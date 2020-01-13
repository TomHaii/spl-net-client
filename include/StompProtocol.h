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

class StompProtocol {
private:
    Client client;
    vector<string>& buildVector(string s);
    vector<string>& getAction(MessageFrame &frame);

public:

    StompProtocol();
    Client &getClient();
    ~StompProtocol();
    void process(Frame &);
    const Frame *buildFrame(std::string &message);

};


#endif //BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
