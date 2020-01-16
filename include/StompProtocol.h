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
    Client& client;
    ConnectionHandler& handler;
    bool terminate = false;
    static vector<string> buildVector(string& s);
    static vector<string> getAction(MessageFrame &frame, vector<string>&);
    void takeAction(MessageFrame &msg, vector<string> &action) const;
    void returnAction(MessageFrame&, vector<string>&) const;
    void borrowAction(MessageFrame&, vector<string>&) const;
    void hasBookAction(MessageFrame&, vector<string>&) const;
    void statusAction(MessageFrame &, vector<string> &) const;
    void messageFrameCase(Frame *frame) const;
    void receiptFrameCase(Frame *frame) ;
    static void getActionType(string& s, string &message);
    Frame *loginCommend(string &message, Frame *frame) const;
    Frame *joinCommend(string &message, Frame *frame) const;
    Frame *logoutCommend(string &message, Frame *frame) const;
    static void buildReturnVector(vector<string> &output, vector<string> &vec);
    static void buildTakeVector(vector<string> &output, vector<string> &vec);
    static void buildBorrowVector(vector<string> &output, vector<string> &vec);
    static void buildHasBookVector(vector<string> &output, vector<string> &vec);
    static void buildAddBookVector(vector<string> &output, vector<string> &vec);




public:
    void markAsTerminated();
    bool shouldTerminate();
    StompProtocol(ConnectionHandler&, Client&);
    ~StompProtocol()= default;
    void process(Frame *);


    Frame *buildFrame(std::string &message);
};


#endif //BOOST_ECHO_CLIENT_STOMPPROTOCOL_H
