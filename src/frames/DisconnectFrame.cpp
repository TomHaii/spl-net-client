//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "frames/DisconnectFrame.h"

int DisconnectFrame::getReceiptId() const {
    return receiptId;
}


string DisconnectFrame::toString() {
    return "DISCONNECT\n"
           "receipt:"+std::to_string(receiptId)+
           "\n\n";
}

DisconnectFrame::DisconnectFrame(int receiptId) : receiptId(receiptId) {}


