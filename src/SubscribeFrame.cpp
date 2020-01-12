//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "SubscribeFrame.h"

const string &SubscribeFrame::getDestination() const {
    return destination;
}

int SubscribeFrame::getId(){
    return id;
}

int SubscribeFrame::getReceipt() {
    return receipt;
}

SubscribeFrame::SubscribeFrame(string & str):destination(""),id(0),receipt(0) {
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
    return "SUBSCRIBE\ndestination:"+destination+"\nid:"+to_string(id)+"\nreceipt:"+to_string(receipt)+'\n'+'\u0000';

}
