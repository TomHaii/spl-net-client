#ifndef BOOST_ECHO_CLIENT_SUBSCRIBEFRAME_H
#define BOOST_ECHO_CLIENT_SUBSCRIBEFRAME_H

#include "Frame.h"
using namespace std;
class SubscribeFrame: public Frame {
private:
    string destination;
    int id;
    int receipt;
public:
    ~SubscribeFrame() override = default;

    int getReceipt();

    SubscribeFrame(string & str, int _id, int _receipt);

    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_SUBSCRIBEFRAME_H
