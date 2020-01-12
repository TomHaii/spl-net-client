//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "ConnectedFrame.h"

ConnectedFrame::ConnectedFrame(vector<string>& msg):version("") {
    for(string& word: msg){
        if(word.find("version") != string::npos){
            version = word.substr(1, word.find(':'));
        }
    }
}

string ConnectedFrame::toString() {
    return "TODO Connectedframe result";
}
