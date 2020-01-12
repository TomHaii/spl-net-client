//
// Created by tomle on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
#define BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H


#include "Frame.h"
#include "ConnectedFrame.h"
#include "MessageFrame.h"
#include "ReceiptFrame.h"



using namespace std;

class stompEncoderDecoder{
private:

public:
    Frame* decodeMessage(string& msg);
};


#endif //BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
