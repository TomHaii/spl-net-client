//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_DISCONNECTFRAME_H
#define BOOST_ECHO_CLIENT_DISCONNECTFRAME_H


#include "Frame.h"

class DisconnectFrame: public Frame {
private:
    int receiptId;
public:
    ~DisconnectFrame() override = default;

    explicit DisconnectFrame(int receiptId);
    int getReceiptId() const;
    string toString() override;

};


#endif //BOOST_ECHO_CLIENT_DISCONNECTFRAME_H
