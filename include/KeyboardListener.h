#ifndef BOOST_ECHO_CLIENT_KEYBOARDLISTENER_H
#define BOOST_ECHO_CLIENT_KEYBOARDLISTENER_H


#include <mutex>
#include "StompProtocol.h"
#include "connectionHandler.h"
using namespace std;

class KeyboardListener {

private:
    ConnectionHandler& handler;
    StompProtocol& stompProtocol;
    bool terminate;
public:
    KeyboardListener(ConnectionHandler& _handler, StompProtocol& _stompProtocol);
    void operator()();

};


#endif //BOOST_ECHO_CLIENT_KEYBOARDLISTENER_H
