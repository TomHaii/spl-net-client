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
    const string &getDestination() const;
    ~SendFrame() override ;
    SendFrame(Client&, string&);
    SendFrame(string, string);
    void returnCommend(Client& client, string &genre, const string &bookName);
    void addCommend(Client& client, string &genre, string &userName, string &bookName);
    string getBookName(vector<string> &vec) const;
    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_SENDFRAME_H
