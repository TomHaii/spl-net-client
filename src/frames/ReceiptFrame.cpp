#include "frames/ReceiptFrame.h"

ReceiptFrame::ReceiptFrame(vector<string>& msg):id(0) {
    for(string& word: msg){
        if(word.find("receipt-id") != string::npos){
            int split = word.find(':');
            word = word.substr(split+1);
            id = stoi(word);
        }
    }
}

string ReceiptFrame::toString() {
    return "RECEIPT\n"
           "receipt-id:"+to_string(id);
}

ReceiptFrame::ReceiptFrame(int _id):id(_id) {

}

int ReceiptFrame::getId() const {
    return id;
}
