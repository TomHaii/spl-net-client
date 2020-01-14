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
    unordered_map<string, vector<Book*>*> *booksMap;
    unordered_map<string, vector<string>*> *requestedBooks;
    string name;
    int subscriptionId;
    int receiptId;
    unordered_map<int, string>* topicsSubscriptionsById;
    unordered_map<int, ReceiptFrame*> *receipts;


public:
    unordered_map<int, string> *getTopicsSubscriptionsById();

    unordered_map<string, vector<string> *> *getRequestedBooks();

    Client(string name);


    Client();

    unordered_map<string, vector<Book*> *> *getBooksMap() const;

    void setBooksMap(unordered_map<string, vector<Book*> *> *booksMap);

    void addReceiptFrame(int id, ReceiptFrame* frame);

    ReceiptFrame* getReceiptById(int id);

    void setName(const string &name);

    int getSubscriptionId() const;

    void setSubscriptionId(int subscriptionId);

    int getReceiptId() const;

    void setReceiptId(int receiptId);

    void incrementSubscriptionId();

    void incrementReceiptId();

    unordered_map<int, ReceiptFrame*> *getReceipts();

    vector<Book*> *getBooksByGenre(string);
    void addBook(Book*);
    const string &getUserName() const;


};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
