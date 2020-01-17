#include "Client.h"
#include <utility>
#include <iostream>
#include <frames/SubscribeFrame.h>
#include <frames/SendFrame.h>

unordered_map<string, vector<Book>> *Client::getBooksMap() const {
    return booksMap;
}


void Client::setName(const string &_name) {
    Client::name = _name;
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

Client::Client():booksMap(new unordered_map<string,vector<Book>>), name(""), subscriptionId(1),receiptId(1),
                receipts(new unordered_map<int, bool>), topicsSubscriptionsById(new unordered_map<int, string>),
                requestedBooks(new unordered_map<string,vector<string>>), booksMap_lock(), requested_lock(), topics_lock(), receipts_lock() {}

vector<Book>& Client::getBooksByGenre(const string& topic){
    return booksMap->at(topic);
}

void Client::addBook(const Book& book) {
    lock_guard<mutex> lock(booksMap_lock); 
    string topic = book.getGenre();
    if(booksMap->count(topic) == 0) {
        vector<Book> vec;
        booksMap->insert(pair<string, vector<Book>>(topic,vec));
    }
    booksMap->at(topic).push_back(book);
}

void Client::addBook(const Book& book, const string& topic, const string& bookName) {
    lock_guard<mutex> lock(booksMap_lock); 
    if(booksMap->count(topic) == 0) {
        vector<Book> vec;
        booksMap->insert(pair<string, vector<Book>>(topic, vec));
    }
    bool exists = false;
    for (Book &b: getBooksByGenre(topic)) {
        if (b.getBookName() == bookName) {
            exists = true;
        }
    }
    if(!exists)
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
    lock_guard<mutex> lock(topics_lock); //
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
    lock_guard<mutex> lock(receipts_lock); //
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

Client::Client(const Client &) {

}

Client &Client::operator=(const Client &t) {
}

void Client::eraseTopic(string &s) {
    lock_guard<mutex> lock(booksMap_lock);
    booksMap->erase(s);
}

void Client::eraseReceipt(int _id) {
    receipts->erase(_id);

}

void Client::setReceiptReceived(int id) {
    receipts->at(id) = true;

}

void Client::freeBook(const string& topic, string& book) {
    lock_guard<mutex> lock(booksMap_lock); 
    vector<Book> &booksList = booksMap->at(topic);
    for (auto &b: booksList) {
        if (b.getBookName() == book) {
            b.free();
            break;
        }
    }

}

void Client::acquireBook(const string& topic, string &book) {
    lock_guard<mutex> lock(booksMap_lock); 
    for (auto &b: booksMap->at(topic)) {
        if (b.getBookName() == book && b.isAvailable()) {
            b.acquire();
            break;
        }

    }

}

Frame* Client::subscribe(const string& topic, Frame* frame, string& message) {
    lock_guard<mutex> lock(booksMap_lock);
    if (booksMap->count(topic) == 0) {
        vector<Book> vec2;
        booksMap->insert(pair<string, vector<Book>>(topic, vec2));
    }
    frame = new SubscribeFrame(message, subscriptionId, receiptId);
    int id = dynamic_cast<SubscribeFrame *>(frame)->getReceipt();
    topicsSubscriptionsById->insert(pair<int, string>(subscriptionId, topic));
    receipts->insert(pair<int, ReceiptFrame *>(id, nullptr));
    incrementReceiptId();
    incrementSubscriptionId();
    return frame;
}

bool Client::letBorrow(const string& topic, string &book) {
    lock_guard<mutex> lock(booksMap_lock); 
    if(booksMap->count(topic)>0) {
        for (auto &b: getBooksByGenre(topic)) {
            if (b.getBookName() == book) {
                if (b.isAvailable()) {
                    b.acquire();
                    return true;
                }
            }
        }
    }
    return false;

}

string Client::takeBook(string &topic, string &book, string &owner) {
    if(requestedBooks->count(topic) > 0) {
        vector<string> &_requestedBooks = getRequestedBooks()->at(topic);
        for (auto &_requestedBook : getRequestedBooks()->at(topic)) {
            if (_requestedBook == book) {
                string str;
                _requestedBooks.erase(remove(_requestedBooks.begin(), _requestedBooks.end(), book),
                                      _requestedBooks.end());
                str.append("Taking ").append(book).append(" from ").append(owner);
                Book b(topic, book, owner);
                addBook(b);
                SendFrame sendFrame(str, topic);
                string m = sendFrame.toString();
                return m;
            }
        }
    }
    return "";
}

string Client::buildBooksList(const string& topic) {
    lock_guard<mutex> lock(booksMap_lock); 
    string books;
    if(booksMap->count(topic)>0) {
        for (auto &b: getBooksByGenre(topic)) {
            if (b.isAvailable()) {
                books.append(b.getBookName() + ",");
            }
        }
    }
    if(!books.empty())
        books = books.substr(0,books.size()-1);
    return books;
}

void Client::addReceipt(int id) {
    lock_guard<mutex> lock(receipts_lock); 
    receipts->insert(pair<int,bool>(id, false));
}

void Client::requestBook(const string& topic, const string& book) {
    lock_guard<mutex> lock(receipts_lock); 
    if(requestedBooks->count(topic) == 0){
        vector<string> vec;
        requestedBooks->insert(pair<string, vector<string>&>(topic,vec));
    }
    getRequestedBooks()->at(topic).push_back(book);
}

void Client::returnBook(string &borrowedFrom, const string& topic, const string& bookName) {
    lock_guard<mutex> lock(booksMap_lock); 
    if(booksMap->count(topic)>0) {
        vector<Book> &booksList = getBooksByGenre(topic);
        for (auto it = booksList.begin(); it != booksList.end(); ++it) {
            Book b = *it;
            if (b.getBookName() == bookName) {
                borrowedFrom = b.getOwner();
                getBooksByGenre(topic).erase(it);
                break;
            }
        }
    }

}
