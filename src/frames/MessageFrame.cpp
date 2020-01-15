//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <iostream>
#include "frames/MessageFrame.h"

const string &MessageFrame::getDestination() const {
    return destination;
}

string &MessageFrame::getBody() {
    return body;
}

MessageFrame::MessageFrame(vector<string>& msg)
        :destination(""), body("") {
    for(string& word: msg){
        if(word.find("destination") != string::npos){
            int split = word.find(':');
            destination = word.substr(split+1);
        }
    }
    body = msg.at(4);

}

string MessageFrame::toString() {
    return body;
}

MessageFrame::~MessageFrame() {
    destination.clear();
    body.clear();
}
