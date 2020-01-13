//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "frames/ReceiptFrame.h"



ReceiptFrame::ReceiptFrame(vector<string>& msg):id(0) {
    for(string& word: msg){
        if(word.find("receipt-id") != string::npos){
            id = stoi(word.substr(1, word.find(':')));
        }
    }
}

string ReceiptFrame::toString() {
    return "receipt " + to_string(id) + " received";
}

ReceiptFrame::ReceiptFrame(int _id):id(_id) {

}

int ReceiptFrame::getId() const {
    return id;
}
