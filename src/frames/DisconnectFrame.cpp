#include "frames/DisconnectFrame.h"


string DisconnectFrame::toString() {
    return "DISCONNECT\n"
           "receipt:"+std::to_string(receiptId)+
           "\n\n";
}

DisconnectFrame::DisconnectFrame(int receiptId) : receiptId(receiptId) {}




