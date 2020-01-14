//
// Created by tomu@wincs.cs.bgu.ac.il on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERLISTENER_H
#define BOOST_ECHO_CLIENT_SERVERLISTENER_H


#include <mutex>
#include "StompProtocol.h"
#include "stompEncoderDecoder.h"
#include "connectionHandler.h"

class connectionHandler;
class stompProtocol;
class stompEncoderDecoder;


using namespace std;
class ServerListener {
private:
    StompProtocol stompProtocol;
    stompEncoderDecoder& stompEncDec;
    ConnectionHandler& connectionHandler;
    bool terminate;
public:
    ServerListener(ConnectionHandler& _connectionHandler, StompProtocol& _stompProtocol, stompEncoderDecoder& _stompEncoderDecoder);
    void operator()();
    void shouldTerminate();

    bool isTerminate() const;
};


#endif //BOOST_ECHO_CLIENT_SERVERLISTENER_H
