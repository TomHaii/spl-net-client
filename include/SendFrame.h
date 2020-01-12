//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SENDFRAME_H
#define BOOST_ECHO_CLIENT_SENDFRAME_H


#include "Frame.h"
#include "Book.h"

using namespace std;
class SendFrame: public Frame {
private:
    string destination;
    string body;
public:
    SendFrame(string&, Book&);

};


#endif //BOOST_ECHO_CLIENT_SENDFRAME_H
