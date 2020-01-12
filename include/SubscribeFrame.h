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
    int id;
    int receipt;
public:
    const string &getDestination() const;

    int getId();

    int getReceipt();

    void setId(int id);

    void setReceipt(int receipt);

    SubscribeFrame(string&);

    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_SUBSCRIBEFRAME_H
