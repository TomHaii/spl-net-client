//
// Created by yaelgeis@wincs.cs.bgu.ac.il on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_ERRORFRAME_H
#define BOOST_ECHO_CLIENT_ERRORFRAME_H


#include "Frame.h"

class ErrorFrame: public Frame{

private:
    int receiptId;
    string body;

public:
    ErrorFrame(vector<string>&);

    int getReceiptId() const;

    const string &getBody() const;

    string toString();
};


#endif //BOOST_ECHO_CLIENT_ERRORFRAME_H
