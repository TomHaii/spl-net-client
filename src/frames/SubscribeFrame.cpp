#include "frames/SubscribeFrame.h"

int SubscribeFrame::getReceipt() {
    return receipt;
}

SubscribeFrame::SubscribeFrame(string & str, int _id, int _receipt):destination(""),id(_id),receipt(_receipt) {
    vector<string> vec = buildVector(str);
    destination = vec.at(1);
}

string SubscribeFrame::toString() {
    return "SUBSCRIBE\n"
           "destination:"+destination+"\n"
           "id:"+to_string(id)+"\n"
           "receipt:"+to_string(receipt)+
           "\n\n";

}
