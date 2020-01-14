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
            vector<string> action = getAction(msg);
            if (action.at(0) == "return") {
                returnAction(msg, action);
            } else if (action.at(0) == "take") {
                takeAction(msg, action);
            } else if (action.at(0) == "borrow") {
                borrowAction(msg, action);
            } else if (action.at(0) == "hasBook") {
                hasBookAction(msg, action);
            } else if (action.at(0) == "add") {
                cout << msg.getBody() << endl;
            } else if (action.at(0) == "status") {
                statusAction(msg, action);
            } else if (action.at(0) == "bookStatusReply") {
                cout << "book status for " + msg.getDestination() + ":\n" + msg.getBody() << endl;
            }
            action.clear();
//            delete(&action);
        } else if (type == CONNECTED) {
            cout << client->getUserName() + " has connected successfully";
        } else if (type == RECEIPT) {
            int id = dynamic_cast<ReceiptFrame *>(frame)->getId();
            if (client->getReceiptById(id) == nullptr) {
                client->getReceipts()->at(id) = dynamic_cast<ReceiptFrame *>(frame);
            } else {
                string topic = client->getTopicsSubscriptionsById()->at(id);
                client->getReceipts()->erase(id);
                client->getBooksMap()->erase(topic);
            }
            cout << frame->toString() << endl;
        } else if (type == ERROR) {
            cout << frame->toString() << endl;
        }
    }
}

void StompProtocol::returnAction(MessageFrame &msg,
                                 vector<string> &action) const{
    cout << msg.getBody() << endl;
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
    cout << msg.getBody() << endl;
    string book = action.at(1);
    if (action.at(2) == client->getUserName()) {
        for (Book *b: *client->getBooksByGenre(msg.getDestination())) {
            if (b->getBookName() == book) {
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
        std::cout << " making new connectframe " << std::endl;
        frame = new ConnectFrame(message);
        string name =  dynamic_cast<ConnectFrame*>(frame)->getLogin();
        client->setName(name);
    }
    else if(type == "join") {
        frame = new SubscribeFrame(message, client->getSubscriptionId(), client->getReceiptId());
        string topic = dynamic_cast<SubscribeFrame*>(frame)->getDestination();
        unordered_map<string, vector<Book*>*> *map = client->getBooksMap();
        if(map->count(topic)==0) {
            client->getRequestedBooks()->insert(pair<string, vector<string> *>(topic, new vector<string>));
            vector<Book *> *vec = new vector<Book *>;
            map->insert(pair<string, vector<Book *> *>(topic, vec));
        }
        int id = dynamic_cast<SubscribeFrame*>(frame)->getReceipt();
        client->getTopicsSubscriptionsById()->insert(pair<int, string>(client->getSubscriptionId(), topic));
        client->getReceipts()->insert(pair<int,ReceiptFrame*>(id, nullptr));
        client->incrementReceiptId();
        client->incrementSubscriptionId();
    }
    else if(type == "exit") {
        frame = new UnsubscribeFrame(message, client);
    }
    else if(type == "logout")
        frame = new DisconnectFrame();
    else {
        SendFrame* sendFrame= new SendFrame(client, message);
        frame = sendFrame; // maybe it wont work
    }
    frame->setType(OTHER);
    return frame;
}


vector<string>& StompProtocol::getAction(MessageFrame& frame) {
    vector<string> vec = buildVector(frame.getBody());
    auto* output = new vector<string>;
    if(vec.at(0) == "returning"){    //0 = return, 1= book, 2= returning to
        output->emplace_back("return");
        string book;
        for (int i = 1; i < vec.size(); i++){
            string s = vec.at(i);
            if (s != "to")
                book.append(s+" ");
            else {
                output->push_back(s);
                break;
            }
        }
        output->push_back(vec.at(vec.size()-1));
    }
    else if(vec.at(0) == "taking") {  //0= take, 1= book, 2= taken from
        output->emplace_back("take");
        string book;
        for (int i = 1; i < vec.size(); i++){
            string s = vec.at(i);
            if (s != "from")
                book.append(s+" ");
            else {
                output->push_back(s);
                break;
            }
        }
        output->push_back(vec.at(vec.size()-1));
    }
    else if(vec.at(1) == "status"){
        output->emplace_back("status");
    }
    else if(vec.at(1) == "wish"){ //0= borrow, 1= name, 2= book
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

    else if (vec.at(1) == "has" && vec.at(2) != "added"){ //0= hasBook, 1= name, 2= book
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
    else if (vec.at(1) == "has" && vec.at(2) == "added"){ //0= add, 1= name, 2= book
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
    else{
        output->emplace_back("bookStatusReply"); //0= bookStatusReply, 1= name, 2+= books
        string msg = frame.getBody();
        string word;
        for(char c : msg){
            if (c == ':' | c == ',' ){
                output->push_back(word);
                word = "";
            }
            else
                word += c;
        }
        output->push_back(word);
    }
    return *output;
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
    cout<<"printing in borrowAction!!"<<endl;

    cout<<msg.toString()<<endl;
    string topic = msg.getDestination();
    string book = vec.at(2);
    for (Book *b: *client->getBooksByGenre(topic)) {
        if (b->getBookName() == book) {
            if (b->isAvailable()) {
                SendFrame sendFrame(client->getUserName() + " has " + book, topic);
                string str = sendFrame.toString();
                handler.sendLine(str);
            }
            break;
        }
    }
}

void StompProtocol::hasBookAction(MessageFrame & msg, vector<string> &vec) const {
    cout<<msg.toString()<<endl;
    string owner = vec.at(1);
    string book = vec.at(2);
    cout<<"book name: "+book <<endl;
    string topic = msg.getDestination();
    for (string &s : *client->getRequestedBooks()->at(topic)){
        if (s == book){
            string str;
            str.append("taking ").append(book).append(" from ").append(owner);
            client->getBooksByGenre(topic)->push_back(new Book(topic, book, owner));
            SendFrame sendFrame(str, topic);
            string m = sendFrame.toString();
            handler.sendLine(m);
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
            str.append(","+b->getBookName());
        }
    }
    SendFrame sendFrame(str, topic);
    string m = sendFrame.toString();
    handler.sendLine(m);
}

StompProtocol::StompProtocol(ConnectionHandler & _handler, Client* cl): handler(_handler), client(cl) {}








