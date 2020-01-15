//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <frames/Frame.h>
#include <frames/MessageFrame.h>
#include <iostream>
#include <connectionHandler.h>
#include "StompProtocol.h"

void StompProtocol::process(Frame* frame) {
    if(frame != nullptr) {
        FrameType type = frame->getType();
        if (type == MESSAGE) {
            MessageFrame msg = *dynamic_cast<MessageFrame *>(frame);
            vector<string>* action = getAction(msg);
            if (action != nullptr) {
                if (action->at(0) == "return") {
                    cout << "i am return" << endl;
                    returnAction(msg, *action);
                } else if (action->at(0) == "take") {
                    takeAction(msg, *action);
                } else if (action->at(0) == "borrow") {
                    borrowAction(msg, *action);
                } else if (action->at(0) == "hasBook") {
                    hasBookAction(msg, *action);
                }
                else if (action->at(0) == "status") {
                    statusAction(msg, *action);
                }

                action->clear();
                //TODO: delete
            }
            else{
                cout<<"i am trying to print but the action is null"<<endl;
            }
        }
        else if (type == RECEIPT) {
            int id = dynamic_cast<ReceiptFrame *>(frame)->getId();
            if(client->getDisconnectReceipt() != id) {
                if (!client->getReceiptById(id)) {
                    client->getReceipts()->at(id) = true;
                } else {
                    string topic = client->getTopicsSubscriptionsById()->at(id);
                    client->getReceipts()->erase(id);
                    client->getBooksMap()->erase(topic);
                }
            }
            else{
                connected=false;
                markAsTerminated();
                cout << "logging out" << endl;
                //TODO: DELETE CLIENT
            }
        }
    }
}

void StompProtocol::returnAction(MessageFrame &msg,
                                 vector<string> &action) const{
    string book = action.at(1);
    if (action.at(2) == client->getUserName()) {
        vector<Book*> booksList = *client->getBooksByGenre(msg.getDestination());
        for (Book* b: booksList){
            if (b->getBookName() == book) {
                b->free();
                break;
            }
        }
    }
}


void StompProtocol::takeAction(MessageFrame &msg,
                                 vector<string> &action) const{
    string book = action.at(1);
    if (action.at(2) == client->getUserName()) {
        for (Book *b: *client->getBooksByGenre(msg.getDestination())) {
            if (b->getBookName() == book && b->isAvailable()) {
                b->acquire();
                break;
            }
        }
    }
}



StompProtocol::~StompProtocol() {

}



Frame* StompProtocol::buildFrame(std::string &message) {
    string type;
    Frame* frame = nullptr;
    for(char c: message){
        if(c == ' '){
            break;
        }
        type += c;
    }
    if(type == "login") {
//        if(connected){
//            __throw_runtime_error("a different user is connected!");
//        }
//        std::cout << " making new connectframe " << std::endl;
        if(handler.connect()) {
            frame = new ConnectFrame(message);
            string name = dynamic_cast<ConnectFrame *>(frame)->getLogin();
            client->setName(name);
        }
        else{
            cout<<"connection error "<<endl;
        }
    }
    else if(type == "join") {
        string topic = message.substr(5);
        unordered_map<string, vector<Book*>*> *map = client->getBooksMap();
        if(map->count(topic)==0) {
            frame = new SubscribeFrame(message, client->getSubscriptionId(), client->getReceiptId());
            client->getRequestedBooks()->insert(pair<string, vector<string> *>(topic, new vector<string>));
            vector<Book *> *vec = new vector<Book *>;
            map->insert(pair<string, vector<Book *> *>(topic, vec));
            int id = dynamic_cast<SubscribeFrame *>(frame)->getReceipt();
            client->getTopicsSubscriptionsById()->insert(pair<int, string>(client->getSubscriptionId(), topic));
            client->getReceipts()->insert(pair<int, ReceiptFrame *>(id, nullptr));
            client->incrementReceiptId();
            client->incrementSubscriptionId();
        }

    }
    else if(type == "exit") {
        string topic = message.substr(5);
        if(client->getBooksMap()->count(topic)>0)
            frame = new UnsubscribeFrame(message, client);

    }
    else if(type == "logout") {
        for(pair <string, vector<Book*>*> p : *client->getBooksMap()){
            string msg = "exit " +p.first;
            UnsubscribeFrame exitFrame (msg, client);
            handler.sendLine(exitFrame.toString());
        }
        int id = client->getReceiptId();
        client->setDisconnectReceipt(id);
        client->getReceipts()->insert(pair<int,bool>(id, false));
        frame = new DisconnectFrame(id);
        client->incrementReceiptId();
    }
    else {
        SendFrame* sendFrame= new SendFrame(client, message);
        frame = sendFrame;
    }
    if(frame != nullptr)
        frame->setType(OTHER);
    return frame;
}


vector<string>* StompProtocol::getAction(MessageFrame& frame) {
    vector<string> vec = buildVector(frame.getBody());
    auto* output = new vector<string>;

    if(vec.at(0) == "Returning"){    //0 = return, 1= book, 2= returning to
        output->emplace_back("return");
        string book;
        for (int i = 1; i < vec.size() - 2; i++){
            string s = vec.at(i);
            book.append(" "+s);
        }
        book = book.substr(1);
        output->push_back(book);
        output->push_back(vec.at(vec.size()-1));
    }
    else if(vec.at(0) == "Taking") {  //0= take, 1= book, 2= taken from
        output->emplace_back("take");
        string book;
        for (int i = 1; i < vec.size() - 2; i++){
            string s = vec.at(i);
            book.append(" "+s);
        }
        book = book.substr(1);
        output->push_back(book);
        output->push_back(vec.at(vec.size()-1));
    }
    else if(vec.size() > 1 && vec.at(1) == "status"){
        output->emplace_back("status");
    }
    else if(vec.size() > 1 && vec.at(1) == "wish"){ //0= borrow, 1= name, 2= book
        output->emplace_back("borrow");
        output->push_back(vec.at(0));
        string book;
        for (int i = 4; i < vec.size(); i++){
            string s = vec.at(i);
            book.append(" "+s);
        }
        book = book.substr(1);
        output->push_back(book);
    }

    else if (vec.size() > 1 && vec.at(1) == "has" && vec.at(2) != "added"){ //0= hasBook, 1= name, 2= book
        output->emplace_back("hasBook");
        output->push_back(vec.at(0));
        string book;
        for (int i = 2; i < vec.size(); i++){
            string s = vec.at(i);
            book.append(" "+s);
        }
        book = book.substr(1);
        output->push_back(book);
    }
    else if (vec.size() > 1 && vec.at(1) == "has" && vec.at(2) == "added"){ //0= add, 1= name, 2= book
        output->emplace_back("add");
        output->push_back(vec.at(0));
        string book;
        for (int i = 5; i < vec.size(); i++){
            string s = vec.at(i);
            book.append(" "+s);
        }
        book = book.substr(1);
        output->push_back(book);
    }
    //replying to book status
    else if (!vec.empty() && vec.at(0) == "Book"){
        output->emplace_back("status"); //0= status, 1=topic
        output->push_back(frame.getDestination());
    }
    else { //0 == bookStatusReply
        output->emplace_back("bookStatusReply");
    }
    return output;
}

vector<string> StompProtocol::buildVector(string& s) {

    string word;
    vector<string> vec;
    for (char c : s){
        if(c == ' ') {
            vec.push_back(word);
            word = "";
        }
        else{
            word += c;
        }
    }
    vec.push_back(word);
    return vec;
}

void StompProtocol::borrowAction(MessageFrame & msg, vector<string> &vec) const {
//    cout<<msg.toString()<<endl;
    string topic = msg.getDestination();
    string book = vec.at(2);
    for (Book *b: *client->getBooksByGenre(topic)) {
        if (b->getBookName() == book) {
            if (b->isAvailable()) {
                SendFrame sendFrame(client->getUserName() + " has " + book, topic);
                b->acquire();
                string str = sendFrame.toString();
                handler.sendLine(str);
            }
            break;
        }
    }
}

void StompProtocol::hasBookAction(MessageFrame & msg, vector<string> &vec) const {
//    cout<<msg.toString()<<endl;
    string owner = vec.at(1);
    string book = vec.at(2);
//    cout<<"book name: "+book <<endl;
    string topic = msg.getDestination();
    vector<string> *requestedBooks = client->getRequestedBooks()->at(topic);
    for (auto & requestedBook : *requestedBooks) {
        {
            if (requestedBook == book){
//                cout << " THE OWNER IS "+ owner + " THE CLIENT IS " + client->getUserName() << endl;
                string str;
                requestedBooks->erase(remove(requestedBooks->begin(), requestedBooks->end(), requestedBook));
                str.append("Taking ").append(book).append(" from ").append(owner);
                client->getBooksByGenre(topic)->push_back(new Book(topic, book, owner));
                SendFrame sendFrame(str, topic);
                string m = sendFrame.toString();
                handler.sendLine(m);
                break;
            }
        }
    }


}

void StompProtocol::statusAction(MessageFrame & msg, vector<string> &vec) const {
    cout << msg.getBody() << endl;
    string topic = msg.getDestination();
    string name = client->getUserName();
    string str = client->getUserName() +":";
    for (Book* b: *client->getBooksByGenre(topic)){
        if (b->isAvailable()){
            str.append(b->getBookName()+",");
        }
    }
    SendFrame sendFrame(str, topic);
    string m = sendFrame.toString();
    handler.sendLine(m);
}

StompProtocol::StompProtocol(ConnectionHandler & _handler, Client* cl): handler(_handler), client(cl) {}

bool StompProtocol::shouldTerminate() {
    return terminate;
}

void StompProtocol::markAsTerminated() {
    terminate = true;
    handler.close();

}

bool StompProtocol::isConnected() const {
    return connected;
}

void StompProtocol::setConnected(bool connected) {
    StompProtocol::connected = connected;
}








