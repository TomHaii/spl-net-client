//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <frames/ConnectFrame.h>
#include <vector>
#include <iostream>

ConnectFrame::ConnectFrame(string & str) {
    vector<string> vec = buildVector(str);
    acceptVersion = "1.2";
    host = vec.at(1);
    login = vec.at(2);
    passcode = vec.at(3);

}

const string &ConnectFrame::getAcceptVersion() const {
    return acceptVersion;
}

const string &ConnectFrame::getHost() const {
    return host;
}

const string &ConnectFrame::getLogin() const {
    return login;
}

const string &ConnectFrame::getPasscode() const {
    return passcode;
}

string ConnectFrame::toString() {
    return "CONNECT\n"
           "accept-version:"+acceptVersion+"\n"+
           "host:"+host+"\n"+
           "login:"+login+"\n"+
           "passcode:"+passcode+
           "\n";
}
