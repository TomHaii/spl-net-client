//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
#define BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
#include <unordered_map>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <frames/MessageFrame.h>
#include "frames/Frame.h"
#include "frames/ConnectFrame.h"
#include "frames/SubscribeFrame.h"
#include "frames/SendFrame.h"
#include "frames/DisconnectFrame.h"
#include "frames/UnsubscribeFrame.h"
#include "Client.h"

class Client;
class Frame;
class MessageFrame;
class ConnectionHandler;

class StompProtocol {
private:
    Client* client;
    ConnectionHandler* handler;
    bool connected = false;
    bool terminate = false;
    static vector<string> buildVector(string& s);
    static vector<string>* getAction(MessageFrame &frame);
    void takeAction(MessageFrame &msg, vector<string> &action) const;
    void returnAction(MessageFrame&, vector<string>&) const;
    void borrowAction(MessageFrame&, vector<string>&) const;
    void hasBookAction(MessageFrame&, vector<string>&) const;
    void statusAction(MessageFrame &, vector<string> &) const;

public:
    bool isConnected() const;
    void setConnected(bool connected);
    void markAsTerminated();
    bool shouldTerminate();
    StompProtocol(ConnectionHandler*, Client*);
    ~StompProtocol();
    void process(Frame *);
    Frame *buildFrame(std::string &message);

};


#endif //BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
