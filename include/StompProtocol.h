//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
#define BOOST_ECHO_CLIENT_STOMPPROTOCOL_H


#include <unordered_map>
#include "Book.h"
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include "Frame.h"
#include "ConnectFrame.h"
#include "SubscribeFrame.h"
#include "SendFrame.h"
#include "DisconnectFrame.h"
#include "UnsubscribeFrame.h"

class StompProtocol {
private:
    unordered_map<string, vector<Book>*> *booksMap;
    string userName;
    int subscriptionId;
    int receiptId;

    vector<string> &buildVector(string s);
    vector<string>& getAction(MessageFrame &frame);
public:
    StompProtocol();
    ~StompProtocol();
    void process(Frame&);

    void incrementSubId();
    void incrementRecIp();
    int getSubscriptionId() const;

    vector<Book> *getBooksByGenre(string&) const;

    unordered_map<string, vector<Book> *> *getBooksMap() const;

    void addBook(Book&);
    const string &getUserName() const;

    int getReceiptId() const;
    const Frame* buildFrame(std::string& message);




};


#endif //BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
