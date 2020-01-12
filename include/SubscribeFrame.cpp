//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "SubscribeFrame.h"

const string &SubscribeFrame::getDestination() const {
    return destination;
}

const string &SubscribeFrame::getId() const {
    return id;
}

const string &SubscribeFrame::getReceipt() const {
    return receipt;
}

SubscribeFrame::SubscribeFrame(string & str) {
    vector<string> vec = buildVector(str);
    destination = vec.at(1);
}

void SubscribeFrame::setId(const string &id) {
    SubscribeFrame::id = id;
}

void SubscribeFrame::setReceipt(const string &receipt) {
    SubscribeFrame::receipt = receipt;
}
