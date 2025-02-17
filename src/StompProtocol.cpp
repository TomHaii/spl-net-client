//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <frames/Frame.h>
#include <frames/MessageFrame.h>
#include <iostream>
#include <connectionHandler.h>
#include "StompProtocol.h"

StompProtocol::StompProtocol(ConnectionHandler & _handler, Client& cl): handler(_handler), client(cl) {}


void StompProtocol::process(Frame* frame) {
    if(frame != nullptr) {
        FrameType type = frame->getType();
        if (type == MESSAGE) {
            messageFrameCase(frame);
        }
        else if (type == RECEIPT) {
            receiptFrameCase(frame);
        }
        else if (type == ERROR){
            markAsTerminated();
        }
    }
}

void StompProtocol::receiptFrameCase(Frame *frame) {
    int id = dynamic_cast<ReceiptFrame *>(frame)->getId();
    if(client.getDisconnectReceipt() != id) {
        if (!client.getReceiptById(id)) {
            client.setReceiptReceived(id);
        } else {
            string topic = client.getTopicsSubscriptionsById()->at(id);
            client.eraseReceipt(id);
            client.eraseTopic(topic);
        }
    }
    else{
        markAsTerminated();
        cout << "logging out" << endl;
    }
}

void StompProtocol::messageFrameCase(Frame *frame) const {
    MessageFrame msg = *dynamic_cast<MessageFrame *>(frame);
    vector<string> action;
    getAction(msg, action);
    if (!action.empty()) {
        if (action.at(0) == "return") {
            returnAction(msg, action);
        } else if (action.at(0) == "take") {
            takeAction(msg, action);
        } else if (action.at(0) == "borrow") {
            borrowAction(msg, action);
        } else if (action.at(0) == "hasBook") {
            hasBookAction(msg, action);
        }
        else if (action.at(0) == "status") {
            statusAction(msg, action);
        }
    }
}


//this is a reaction function to the "returning book to ___" message
void StompProtocol::returnAction(MessageFrame &msg,
                                 vector<string> &action) const {
    string book = action.at(1);
    if (action.at(2) == client.getUserName()) {
        if(client.getBooksMap()->count(msg.getDestination())>0) {
            client.freeBook(msg.getDestination(), book);
        }
    }
}

//this is a reaction function to the "taking book from ___" message
void StompProtocol::takeAction(MessageFrame &msg,
                                 vector<string> &action) const{
    string book = action.at(1);
    if (action.at(2) == client.getUserName()) {
        client.acquireBook(msg.getDestination(), book);

    }
}



Frame* StompProtocol::buildFrame(std::string &message) {
    Frame* frame = nullptr;
    string type;
    getActionType(type, message);
    if(type == "login") {
        frame = loginCommend(message,frame);
    }
    else if(type == "join") {
        frame = joinCommend(message,frame);
    }
    else if(type == "exit") {
        string topic = message.substr(5);
//        if(client.getBooksMap()->count(topic)>0)
            frame = new UnsubscribeFrame(message, client);
    }
    else if(type == "logout") {
        frame = logoutCommend(message,frame);    }
    else {
        frame = new SendFrame(client, message);
    }
    if(frame != nullptr)
        frame->setType(OTHER);
    return frame;
}


//builds a new frame to the join commend from keyboard
Frame *StompProtocol::joinCommend(string &message, Frame *frame)  const{
    string topic = message.substr(5);
    return client.subscribe(topic, frame, message);
}


vector<string> StompProtocol::getAction(MessageFrame& frame, vector<string>& output) {
    vector<string> vec = buildVector(frame.getBody());
    if(vec.at(0) == "Returning"){    //0 = return, 1= book, 2= returning to
        buildReturnVector(output,vec);
    }
    else if(vec.at(0) == "Taking") {  //0= take, 1= book, 2= taken from
        buildTakeVector(output,vec);
    }
    else if(vec.size() > 1 && vec.at(1) == "status"){
        output.emplace_back("status");
    }
    else if(vec.size() > 1 && vec.at(1) == "wish"){ //0= borrow, 1= name, 2= book
        buildBorrowVector(output,vec);
    }
    else if (vec.size() > 1 && vec.at(1) == "has" && vec.at(2) != "added"){ //0= hasBook, 1= name, 2= book
        buildHasBookVector(output, vec);
    }
    else if (vec.size() > 1 && vec.at(1) == "has" && vec.at(2) == "added"){ //0= add, 1= name, 2= book
        buildAddBookVector(output,vec);
    }
    //replying to book status
    else if (!vec.empty() && vec.at(0) == "Book"){
        output.emplace_back("status"); //0= status, 1=topic
        output.push_back(frame.getDestination());
    }
    else { //0 == bookStatusReply
        output.emplace_back("bookStatusReply");
    }
    return output;
}

void StompProtocol::buildReturnVector(vector<string> &output, vector<string> &vec) {
    output.emplace_back("return");
    string book;
    for (unsigned int i = 1; i < vec.size() - 2; i++){
        string s = vec.at(i);
        book.append(" "+s);
    }
    book = book.substr(1);
    output.push_back(book);
    output.push_back(vec.at(vec.size()-1));
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

//this is a reaction function to the "__ wish to borrow book" message
void StompProtocol::borrowAction(MessageFrame & msg, vector<string> &vec) const {
    const string& topic = msg.getDestination();
    string book = vec.at(2);
    if(client.letBorrow(topic, book)) {
        SendFrame sendFrame(client.getUserName() + " has " + book, topic);
        string str = sendFrame.toString();
        cout << "***printing: " + str << endl;
        handler.sendLine(str);
    }

}

//this is a reaction function to the "___ has book" message
void StompProtocol::hasBookAction(MessageFrame & msg, vector<string> &vec) const {
    string owner = vec.at(1);
    string book = vec.at(2);
    string topic = msg.getDestination();
    string m = client.takeBook(topic, book, owner);
    if(!m.empty())
        handler.sendLine(m);

}

//this is a reaction function to the "Book status" message
void StompProtocol::statusAction(MessageFrame & msg, vector<string> &vec) const {
    const string& topic = msg.getDestination();
    string name = client.getUserName();
    string books = client.buildBooksList(topic);
    string str =  client.getUserName() +":" +books;
    SendFrame sendFrame(str, topic);
    string m = sendFrame.toString();
    handler.sendLine(m);
}


bool StompProtocol::shouldTerminate() {
    return terminate;
}

void StompProtocol::markAsTerminated() {
    terminate = true;
    handler.close();

}

void StompProtocol::getActionType(string &type, string &message) {
    for(char c: message){
        if(c == ' '){
            break;
        }
        type += c;
    }

}

//builds a new frame to the logout commend from keyboard
Frame *StompProtocol::logoutCommend(string &message, Frame *frame) const {
    int id = client.getReceiptId();
    client.setDisconnectReceipt(id);
    client.addReceipt(id);
    frame = new DisconnectFrame(id);
    client.incrementReceiptId();
    return frame;
}

//builds a new frame to the login commend from keyboard
Frame *StompProtocol::loginCommend(string &message, Frame *frame) const {
    if(handler.connect()) {
        frame = new ConnectFrame(message);
        string name = dynamic_cast<ConnectFrame *>(frame)->getLogin();
        client.setName(name);
        return frame;
    }
    else{
        cout<<"connection error "<<endl;
        return nullptr;
    }
}

void StompProtocol::buildTakeVector(vector<string> &output, vector<string> &vec) {
    output.emplace_back("take");
    string book;
    for (unsigned int i = 1; i < vec.size() - 2; i++){
        string s = vec.at(i);
        book.append(" "+s);
    }
    book = book.substr(1);
    output.push_back(book);
    output.push_back(vec.at(vec.size()-1));

}

void StompProtocol::buildBorrowVector(vector<string> &output, vector<string> &vec) {
    output.emplace_back("borrow");
    output.push_back(vec.at(0));
    string book;
    for (unsigned int i = 4; i < vec.size(); i++){
        string s = vec.at(i);
        book.append(" "+s);
    }
    book = book.substr(1);
    output.push_back(book);
}

void StompProtocol::buildHasBookVector(vector<string> &output, vector<string> &vec) {
    output.emplace_back("hasBook");
    output.push_back(vec.at(0));
    string book;
    for (unsigned int i = 2; i < vec.size(); i++){
        string s = vec.at(i);
        book.append(" "+s);
    }
    book = book.substr(1);
    output.push_back(book);
}

void StompProtocol::buildAddBookVector(vector<string> &output, vector<string> &vec) {
    output.emplace_back("add");
    output.push_back(vec.at(0));
    string book;
    for (unsigned int i = 5; i < vec.size(); i++){
        string s = vec.at(i);
        book.append(" "+s);
    }
    book = book.substr(1);
    output.push_back(book);
}







