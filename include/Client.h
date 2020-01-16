//
// Created by yaelgeis@wincs.cs.bgu.ac.il on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <frames/ReceiptFrame.h>


#include "Book.h"

using namespace std;

class Client {
private:
    unordered_map<string, vector<Book>*> *booksMap;
    unordered_map<string, vector<string>*> *requestedBooks;
    string name;
    int subscriptionId;
    int receiptId;
    unordered_map<int, string>* topicsSubscriptionsById;
    int disconnectReceipt = -1;
    unordered_map<int, bool> *receipts;


public:
    Client();
    virtual ~Client();
    unordered_map<int, string> *getTopicsSubscriptionsById();
    unordered_map<string, vector<string>*> *getRequestedBooks();
    unordered_map<string, vector<Book> *> *getBooksMap() const;
    int getSubscriptionIdByTopic(string& topic);
    bool getReceiptById(int id);
    void setName(const string &name);
    int getSubscriptionId() const;
    int getReceiptId() const;
    void incrementSubscriptionId();
    void incrementReceiptId();
    unordered_map<int, bool> *getReceipts();
    vector<Book> *getBooksByGenre(string);
    void addBook(const Book&);
    const string &getUserName() const;
    void setDisconnectReceipt(int _disconnectReceipt);
    int getDisconnectReceipt() const;
};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
