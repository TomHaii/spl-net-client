//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGEFRAME_H
#define BOOST_ECHO_CLIENT_MESSAGEFRAME_H


#include "Frame.h"
using namespace std;
class MessageFrame {
private:
    int subscriptionId;
    int messageId;
    string destination;
    string body;
public:
    MessageFrame(int subscriptionId, int messageId, const string &destination, const string &body);

    int getSubscriptionId() const;

    int getMessageId() const;

    const string &getDestination() const;

    const string &getBody() const;
};


#endif //BOOST_ECHO_CLIENT_MESSAGEFRAME_H
