//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "frames/SubscribeFrame.h"

const string &SubscribeFrame::getDestination() const {
    return destination;
}

int SubscribeFrame::getId(){
    return id;
}

int SubscribeFrame::getReceipt() {
    return receipt;
}

SubscribeFrame::SubscribeFrame(string & str, int _id, int _receipt):destination(""),id(_id),receipt(_receipt) {
    vector<string> vec = buildVector(str);
    destination = vec.at(1);
}

void SubscribeFrame::setId(int _id) {
    id = _id;
}

void SubscribeFrame::setReceipt(int _receipt) {
    receipt = _receipt;
}

string SubscribeFrame::toString() {
    return "SUBSCRIBE\n"
           "destination:"+destination+"\n"
           "id:"+to_string(id)+"\n"
           "receipt:"+to_string(receipt)+
           "\n"+'\0';

}
