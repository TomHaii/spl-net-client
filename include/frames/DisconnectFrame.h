#ifndef BOOST_ECHO_CLIENT_DISCONNECTFRAME_H
#define BOOST_ECHO_CLIENT_DISCONNECTFRAME_H


#include "Frame.h"

class DisconnectFrame: public Frame {
private:
    int receiptId;
public:
    DisconnectFrame():receiptId(0) {}
    ~DisconnectFrame() override = default;
    explicit DisconnectFrame(int receiptId);
    string toString() override;

};


#endif //BOOST_ECHO_CLIENT_DISCONNECTFRAME_H
