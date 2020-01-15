//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SENDFRAME_H
#define BOOST_ECHO_CLIENT_SENDFRAME_H


#include "Frame.h"
#include "Book.h"
#include "StompProtocol.h"

class Client;

using namespace std;

class SendFrame: public Frame {
private:
    string destination;
    string body;
public:
    ~SendFrame() override ;

    SendFrame(Client*, string&);

    SendFrame(string, string);

    const string &getDestination() const;

    const string &getBody() const;

    void returnCommend(Client& client, string &genre, const string &bookName);

    void addCommend(Client& client, string &genre, string &userName, string &bookName);

    string getBookName(vector<string> &vec) const;


    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_SENDFRAME_H
