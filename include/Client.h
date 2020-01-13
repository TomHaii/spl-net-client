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
    string name;
    int subscriptionId;
    int receiptId;
    unordered_map<int, ReceiptFrame> *receipts;


public:
    Client(const string &name);

    Client();

    unordered_map<string, vector<Book> *> *getBooksMap() const;

    void setBooksMap(unordered_map<string, vector<Book> *> *booksMap);

    const string &getName() const;

    void setName(const string &name);

    int getSubscriptionId() const;

    void setSubscriptionId(int subscriptionId);

    int getReceiptId() const;

    void setReceiptId(int receiptId);

    void incrementSubscriptionId();

    void incrementReceiptId();

    vector<Book> *getBooksByGenre(string&) const;
    void addBook(Book&);
    const string &getUserName() const;


};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
