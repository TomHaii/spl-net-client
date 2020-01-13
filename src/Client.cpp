//
// Created by yaelgeis@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "Client.h"

unordered_map<string, vector<Book> *> *Client::getBooksMap() const {
    return booksMap;
}

void Client::setBooksMap(unordered_map<string, vector<Book> *> *booksMap) {
    Client::booksMap = booksMap;
}

const string &Client::getName() const {
    return name;
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

Client::Client(const string &_name) : booksMap(new unordered_map<string,vector<Book>*>), name(_name), subscriptionId(1),receiptId(1), receipts(new unordered_map<int, ReceiptFrame>) {}

Client::Client(): booksMap(new unordered_map<string,vector<Book>*>), name(""), subscriptionId(0),receiptId(0), receipts(new unordered_map<int, ReceiptFrame>) {}

vector<Book> *Client::getBooksByGenre(string & topic) const {
    return booksMap->at(topic);
}

void Client::addBook(Book & book) {
    string topic = book.getGenre();
    if(booksMap->at(topic) == nullptr)
        booksMap->at(topic) = new vector<Book>;
    booksMap->at(topic)->push_back(book);
}

const string &Client::getUserName() const {
    return name;
}

void Client::addReceiptFrame(int id, ReceiptFrame &frame) {
    receipts->at(id) = frame;
}

Frame& Client::getReceiptById(int id) {
    return receipts->at(id);

}

unordered_map<int, ReceiptFrame> *Client::getReceipts() const {
    return receipts;
}
