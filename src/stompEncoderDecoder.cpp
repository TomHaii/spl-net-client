//
// Created by tomle on 10/01/2020.
//

#include <stompEncoderDecoder.h>


Frame *stompEncoderDecoder::decodeMessage(string &msg) {
    vector<string> vec;
    string word;
    for(char c: msg){
        if(c == '\n') {
            vec.push_back(word);
            word = "";
        }
        word += c;
    }
    string type = vec.at(0);
    if(type == "CONNECTED"){
        ConnectedFrame* frame = new ConnectedFrame(vec);
        return frame;
    }
    else if(type == "RECEIPT"){
        ReceiptFrame* frame = new ReceiptFrame(vec);
        return frame;
    }
    else if(type == "MESSAGE"){
        MessageFrame* frame = new MessageFrame(vec);
    }
}
