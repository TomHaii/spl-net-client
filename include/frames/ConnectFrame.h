//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <string>
#include "Frame.h"

#ifndef BOOST_ECHO_CLIENT_CONNECTFRAME_H
#define BOOST_ECHO_CLIENT_CONNECTFRAME_H
using namespace std;

class ConnectFrame : public Frame{
private:

    string acceptVersion;
    string host;
    string login;
    string passcode;

public:
    const string &getAcceptVersion() const;
    const string &getHost() const;
    const string &getLogin() const;
    const string &getPasscode() const;
    ConnectFrame(string&);
    string toString() override;

//    ConnectFrame();
};

#endif //BOOST_ECHO_CLIENT_CONNECTFRAME_H

