//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <iostream>
#include "frames/UnsubscribeFrame.h"



int UnsubscribeFrame::getId() {
    return id;
}


void UnsubscribeFrame::setId(int _id) {
    id = _id;
}

string UnsubscribeFrame::toString() {
    return "UNSUBSCRIBE\n"
           "id:"+to_string(id)+
           "\n";
}

UnsubscribeFrame::UnsubscribeFrame(string& str, Client * client):id(0) {
    vector<string> vec = buildVector(str);
    string topic = vec.at(1);
    id = client->getSubscriptionIdByTopic(topic);
}
