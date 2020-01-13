//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "frames/DisconnectFrame.h"

int DisconnectFrame::getReceiptId() const {
    return receiptId;
}

void DisconnectFrame::setReceiptId(int receiptId) {
    DisconnectFrame::receiptId = receiptId;
}

string DisconnectFrame::toString() {
    return "DISCONNECT\nreceipt:"+std::to_string(receiptId)+'\n' + '\u0000';
}


