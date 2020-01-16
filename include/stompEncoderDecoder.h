
#ifndef BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
#define BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H


#include "frames/Frame.h"
#include "frames/ConnectedFrame.h"
#include "frames/MessageFrame.h"
#include "frames/ReceiptFrame.h"



using namespace std;

class stompEncoderDecoder{
private:
public:
    static Frame* decodeMessage(string& msg);

    static void buildVector(string &msg, vector<string> &vec);
};


#endif //BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
