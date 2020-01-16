#ifndef BOOST_ECHO_CLIENT_UNSUBSCRIBEFRAME_H
#define BOOST_ECHO_CLIENT_UNSUBSCRIBEFRAME_H

#include <Client.h>
#include "Frame.h"


using namespace std;
class UnsubscribeFrame: public Frame {
private:
    int id;
public:
    ~UnsubscribeFrame() override = default;
    UnsubscribeFrame(string& str, Client&);
    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_UNSUBSCRIBEFRAME_H
