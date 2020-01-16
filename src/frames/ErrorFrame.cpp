#include "frames/ErrorFrame.h"

ErrorFrame::ErrorFrame(vector<string> &vec, string& s) {
    for (string &word: vec) {
        if (word.find("receipt-id") != string::npos) {
            int split = word.find(':');
            word = word.substr(split + 1);
            stoi(word);
            break;
        }
    }
    body = s;
}

string ErrorFrame::toString() {
    return body;
}

ErrorFrame::~ErrorFrame() {
    body.clear();
}
