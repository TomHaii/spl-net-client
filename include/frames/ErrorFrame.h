#ifndef BOOST_ECHO_CLIENT_ERRORFRAME_H
#define BOOST_ECHO_CLIENT_ERRORFRAME_H


#include "Frame.h"

class ErrorFrame: public Frame{

private:
    string body;

public:
    ~ErrorFrame() override ;
    ErrorFrame(vector<string>&, string&);
    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_ERRORFRAME_H
