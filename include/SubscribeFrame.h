//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SUBSCRIBEFRAME_H
#define BOOST_ECHO_CLIENT_SUBSCRIBEFRAME_H


#include "Frame.h"
using namespace std;
class SubscribeFrame: public Frame {
private:
    string destination;
    string id;
    string receipt;
public:
    const string &getDestination() const;

    const string &getId() const;

    const string &getReceipt() const;

    void setId(const string &id);

    void setReceipt(const string &receipt);

    SubscribeFrame(string&);
};


#endif //BOOST_ECHO_CLIENT_SUBSCRIBEFRAME_H
