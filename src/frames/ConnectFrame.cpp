#include <frames/ConnectFrame.h>
#include <vector>

ConnectFrame::ConnectFrame(string & str) {
    vector<string> vec = buildVector(str);
    acceptVersion = "1.2";
    host = vec.at(1);
    login = vec.at(2);
    passcode = vec.at(3);

}


const string &ConnectFrame::getLogin() const {
    return login;
}



string ConnectFrame::toString() {
    return "CONNECT\n"
           "accept-version:"+acceptVersion+"\n"+
           "host:"+host+"\n"+
           "login:"+login+"\n"+
           "passcode:"+passcode+
           "\n\n";
}


