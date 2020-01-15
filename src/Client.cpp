//
// Created by yaelgeis@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "Client.h"

#include <utility>
#include <iostream>

unordered_map<string, vector<Book*> *> *Client::getBooksMap() const {
    return booksMap;
}

void Client::setBooksMap(unordered_map<string, vector<Book*> *> *booksMap) {
    Client::booksMap = booksMap;
}


void Client::setName(const string &name) {
    Client::name = name;
}

int Client::getSubscriptionId() const {
    return subscriptionId;
}

void Client::setSubscriptionId(int subscriptionId) {
    Client::subscriptionId = subscriptionId;
}

int Client::getReceiptId() const {
    return receiptId;
}

void Client::setReceiptId(int receiptId) {
    Client::receiptId = receiptId;
}

void Client::incrementReceiptId() {
    receiptId++;

}

void Client::incrementSubscriptionId() {
    subscriptionId++;

}


Client::Client(): booksMap(new unordered_map<string,vector<Book*>*>), name(""), subscriptionId(1),receiptId(1), receipts(new unordered_map<int, bool>), topicsSubscriptionsById(new unordered_map<int, string>),requestedBooks(new unordered_map<string,vector<string>*>) {}

vector<Book*> *Client::getBooksByGenre(string topic){
    if (booksMap->count(topic)==0)
        return nullptr;
    return booksMap->at(topic);
}

void Client::addBook(Book* book) {
    string topic = book->getGenre();
    if(booksMap->count(topic) == 0) {
        booksMap->insert(pair<string, vector<Book *> *>(topic, new vector<Book *>));
        requestedBooks->insert(pair<string, vector<string>*>(topic, new vector<string>));
    }
    booksMap->at(topic)->push_back(book);
}

const string &Client::getUserName() const {
    return name;
}

void Client::addReceiptFrame(int id, ReceiptFrame *frame) {
    receipts->at(id) = frame;
}

bool Client::getReceiptById(int id) {
    return receipts->at(id);

}

unordered_map<int, bool> *Client::getReceipts() {
    return receipts;
}

unordered_map<int, string> *Client::getTopicsSubscriptionsById() {
    return topicsSubscriptionsById;
}

unordered_map<string, vector<string> *> *Client::getRequestedBooks()  {
    return requestedBooks;
}

Client::Client(string _name): booksMap(new unordered_map<string,vector<Book*>*>), name(std::move(_name)), subscriptionId(1),receiptId(1), receipts(new unordered_map<int, bool>), topicsSubscriptionsById(new unordered_map<int, string>),requestedBooks(new unordered_map<string,vector<string>*>) {}

int Client::getSubscriptionIdByTopic(string& topic) {
    for(pair<int,string> p: *topicsSubscriptionsById){
        cout << p.second << endl;
        if(p.second == topic)
            return p.first;
    }
    return -1;
}

int Client::getDisconnectReceipt() const {
    return disconnectReceipt;
}

void Client::setDisconnectReceipt(int _disconnectReceipt) {
    disconnectReceipt = _disconnectReceipt;
}

Client::~Client() {
    for (pair<string, vector<Book *> *> p : *booksMap) {
        p.second->clear(); //TODO: maybe we need to manually delete
    }
    booksMap->clear();
    delete (booksMap);
    for (pair<string, vector<string> *> p : *requestedBooks) {
        p.second->clear();
    }
    requestedBooks->clear();
    delete(requestedBooks);
    topicsSubscriptionsById->clear();
    delete(topicsSubscriptionsById);
    receipts->clear();
    delete(receipts);
}
