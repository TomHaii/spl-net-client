//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <Frame.h>
#include "StompProtocol.h"

void StompProtocol::process(Frame& frame) {

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
