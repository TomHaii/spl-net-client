#include "Client.h"
#include <utility>
#include <iostream>

unordered_map<string, vector<Book>> *Client::getBooksMap() const {
    return booksMap;
}


void Client::setName(const string &_name) {
    Client::name = _name;
}

int Client::getSubscriptionId() const {
    return subscriptionId;
}

int Client::getReceiptId() const {
    return receiptId;
}

void Client::incrementReceiptId() {
    receiptId++;

}

void Client::incrementSubscriptionId() {
    subscriptionId++;

}

Client::Client(): booksMap(new unordered_map<string,vector<Book>>), name(""), subscriptionId(1),receiptId(1), receipts(new unordered_map<int, bool>), topicsSubscriptionsById(new unordered_map<int, string>),requestedBooks(new unordered_map<string,vector<string>>) {}

vector<Book>& Client::getBooksByGenre(const string& topic){
    return booksMap->at(topic);
}

void Client::addBook(const Book& book) {
    string topic = book.getGenre();
    if(booksMap->count(topic) == 0) {
        vector<Book> vec;
        vector<string> vec2;
        booksMap->insert(pair<string, vector<Book>>(topic,vec));
        requestedBooks->insert(pair<string, vector<string>>(topic, vec2));
    }
    booksMap->at(topic).push_back(book);
}

const string &Client::getUserName() const {
    return name;
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

unordered_map<string, vector<string>> *Client::getRequestedBooks()  {
    return requestedBooks;
}

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
    booksMap->clear();
    delete(booksMap);
    requestedBooks->clear();
    delete(requestedBooks);
    topicsSubscriptionsById->clear();
    delete(topicsSubscriptionsById);
    receipts->clear();
    delete(receipts);
}
