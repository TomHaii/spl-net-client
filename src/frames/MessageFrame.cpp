//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

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
            destination = word.substr(1, word.find(':'));
        }
    }
    body = msg.at(4);
}

string MessageFrame::toString() {
    return "TODO: result message for messageframe";
}
