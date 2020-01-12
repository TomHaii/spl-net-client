//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <Frame.h>
#include <MessageFrame.h>
#include "StompProtocol.h"

void StompProtocol::process(Frame& frame) {
    FrameType type = frame.getType();
    if (type == MESSAGE){
        vector<string> action = getAction(dynamic_cast<MessageFrame &>(frame));
    }

}

StompProtocol::~StompProtocol() {

}

StompProtocol::StompProtocol():booksMap(new unordered_map<string, vector<Book>*>), userName(""), subscriptionId(1), receiptId(1) {
}

int StompProtocol::getSubscriptionId() const {
    return subscriptionId;
}

int StompProtocol::getReceiptId() const {
    return receiptId;
}

void StompProtocol::incrementRecIp() {
    receiptId++;
}

void StompProtocol::incrementSubId() {
    subscriptionId++;
}

const string &StompProtocol::getUserName() const {
    return userName;
}

vector<Book> *StompProtocol::getBooksByGenre(string& genre) const {
    return booksMap->at(genre);
}

void StompProtocol::addBook(Book &book) {
    booksMap->at(book.getGenre())->push_back(book);
}

const Frame* StompProtocol::buildFrame(std::string &message) {
    string type;
    Frame* frame = nullptr;
    for(char c: message){
        if(c == ' '){
            break;
        }
        type += c;
    }
    if(type == "login")
        frame = new ConnectFrame(message);
    else if(type == "join")
        frame = new SubscribeFrame(message);
    else if(type == "exit")
        frame = new UnsubscribeFrame(message);
    else if(type == "logout")
        frame = new DisconnectFrame();
    else {
        SendFrame* sendFrame= new SendFrame();
        sendFrame->buildSend(*this, message);
        frame = sendFrame; // maybe it wont work
    }
    frame->setType(OTHER);
    return frame;
}

unordered_map<string, vector<Book> *> *StompProtocol::getBooksMap() const {
    return booksMap;
}

vector<string>& StompProtocol::getAction(MessageFrame &frame) {
    vector<string> vec = buildVector(frame.getBody());
    vector<string> output;
    if(vec.at(0) == "returning"){    //0 = action, 1= book, 2= returning to
        output.emplace_back("return");
        string book = "";
        for (int i = 1; i < vec.size(); i++){
            string s = vec.at(i);
            if (s != "to")
                book.append(s+" ");
            else {
                output.push_back(s);
                break;
            }
        }
        output.push_back(vec.at(vec.size()-1));
    }
    else if(vec.at(0) == "taking") {  //0= action, 1= book, 2= taken from
        output.emplace_back("take");
        string book = "";
        for (int i = 1; i < vec.size(); i++){
            string s = vec.at(i);
            if (s != "from")
                book.append(s+" ");
            else {
                output.push_back(s);
                break;
            }
        }
        output.push_back(vec.at(vec.size()-1));
    }
    else if(vec.at(1) == "status"){
        output.emplace_back("status");
    }
    else if(vec.at(1) == "wish"){ //0= borrow, 1= name, 2= book
        output.emplace_back("borrow");
        output.push_back(vec.at(0));
        string book = "";
        for (int i = 4; i < vec.size(); i++){
            string s = vec.at(i);
            book.append(s+" ");
        }
        output.push_back(book);

    }
    else if (vec.at(1) == "has" && vec.at(2) != "added"){ //0= has book, 1= name, 2= book
        output.emplace_back("has book");
        output.push_back(vec.at(0));
        string book = "";
        for (int i = 1; i < vec.size(); i++){
            string s = vec.at(i);
            book.append(s+" ");
        }
        output.push_back(book);
    }
    else if (vec.at(1) == "has" && vec.at(2) == "added"){ //0= add, 1= name, 2= book
        output.emplace_back("add");
        output.push_back(vec.at(0));
        string book = "";
        for (int i = 5; i < vec.size(); i++){
            string s = vec.at(i);
            book.append(s+" ");
        }
        output.push_back(book);
    }
    //replying to book status
    else{
        output.emplace_back("reply"); //0= reply, 1= name, 2+= books
        string msg = frame.getBody();
        string word = "";
        for(int i = 0; i<msg.size(); i++){
            char c = msg.at(i);
            if (c == ':' | c == ',' ){
                output.push_back(word);
                word = "";
            }
            else
                word += c;
        }
        output.push_back(word);
    }
    return output;
}

vector<string> &StompProtocol::buildVector(string s) {
    string word = "";
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
    return vec;
}
