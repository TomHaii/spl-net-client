//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
#define BOOST_ECHO_CLIENT_STOMPPROTOCOL_H


#include "Book.h"

class StompProtocol {
private:
    vector<Book>* books;
    string userName;
    int subscriptionId;

public:
    StompProtocol();
    ~StompProtocol();
    void process(Frame&);
};


#endif //BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
