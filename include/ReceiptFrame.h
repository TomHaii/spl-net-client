//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_RECEIPTFRAME_H
#define BOOST_ECHO_CLIENT_RECEIPTFRAME_H


#include "Frame.h"

class ReceiptFrame: public Frame {
private:
    int id;
public:
    ReceiptFrame();
    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_RECEIPTFRAME_H
