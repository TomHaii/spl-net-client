//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SENDFRAME_H
#define BOOST_ECHO_CLIENT_SENDFRAME_H


#include "Frame.h"
#include "Book.h"
#include "StompProtocol.h"

class StompProtocol;

using namespace std;
class SendFrame: public Frame {
private:
    string destination;
    string body;
public:
    SendFrame();

    const string &getDestination() const;

    const string &getBody() const;

    void returnCommend(StompProtocol &stompProtocol, string &genre, const string &bookName);

    void addCommend(StompProtocol &stompProtocol, string &genre, string &userName, string &bookName);

    string getBookName(vector<string> &vec) const;

    void buildSend(StompProtocol& stompProtocol ,string &str);

    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_SENDFRAME_H
