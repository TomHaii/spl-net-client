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
            receiptId = stoi(word.substr(1, word.find(':')));
        } else if (word.find("message") != string::npos) {
            body = word.substr(1, word.find(':'));
        }
    }
}

string ErrorFrame::toString() {
    return "Error: "+body;
}
