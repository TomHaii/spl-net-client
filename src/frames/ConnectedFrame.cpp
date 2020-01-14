//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "frames/ConnectedFrame.h"

ConnectedFrame::ConnectedFrame(vector<string>& msg):version("") {
    for(string& word: msg){
        if(word.find("version") != string::npos){
            int split = word.find(':');
            version = word.substr(split+1);
        }
    }
}

string ConnectedFrame::toString() {
    return "CONNECTED\n"
           "version:" + version;
}
