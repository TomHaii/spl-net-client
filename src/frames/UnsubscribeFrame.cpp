//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

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

UnsubscribeFrame::UnsubscribeFrame(string& str):id(0) {
    vector<string> vec = buildVector(str);
    destination = vec.at(1);
}
