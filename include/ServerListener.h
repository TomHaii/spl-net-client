//
// Created by tomu@wincs.cs.bgu.ac.il on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERLISTENER_H
#define BOOST_ECHO_CLIENT_SERVERLISTENER_H


#include <mutex>
#include "StompProtocol.h"
#include "stompEncoderDecoder.h"
#include "connectionHandler.h"
using namespace std;

class ServerListener {

private:
    StompProtocol stompProtocol;
    ConnectionHandler& connectionHandler;
    bool terminate;
public:
    ServerListener(ConnectionHandler& _connectionHandler, StompProtocol& _stompProtocol);
    void operator()();
};


#endif //BOOST_ECHO_CLIENT_SERVERLISTENER_H
