//
// Created by yaelgeis@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "frames/ErrorFrame.h"

int ErrorFrame::getReceiptId() const {
    return receiptId;
}

const string &ErrorFrame::getBody() const {
    return body;
}

ErrorFrame::ErrorFrame(vector<string> &vec) {
    for (string &word: vec) {
        if (word.find("receipt-id") != string::npos) {
            int split = word.find(':');
            word = word.substr(split+1);
            receiptId = stoi(word);
        } else if (word.find("message") != string::npos) {
            int split = word.find(':');
            body = word.substr(split+1);
        }
    }
}

string ErrorFrame::toString() {
    return "Error: "+body;
}

ErrorFrame::~ErrorFrame() {
    body.clear();

}
