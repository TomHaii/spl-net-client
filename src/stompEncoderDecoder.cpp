//
// Created by tomle on 10/01/2020.
//

#include <stompEncoderDecoder.h>
#include <frames/ErrorFrame.h>
#include <iostream>


Frame *stompEncoderDecoder::decodeMessage(string &msg) {
    vector<string> vec;
    string word;
    std::cout << " THE MESSAGE IS " + msg << std::endl;
    for(char c: msg){
        if(c == '\n') {
            if (!word.empty()) {
                vec.push_back(word);
                word = "";
            }
        }
        else
            word += c;
    }
    string type = vec.at(0);
    if(type == "CONNECTED"){
        ConnectedFrame* frame = new ConnectedFrame(vec);
        frame->setType(CONNECTED);
        return frame;
    }
    else if(type == "RECEIPT"){
        ReceiptFrame* frame = new ReceiptFrame(vec);
        frame->setType(RECEIPT);
        return frame;
    }
    else if(type == "MESSAGE"){
        MessageFrame* frame = new MessageFrame(vec);
        frame->setType(MESSAGE);
        return frame;
    } else if (type == "ERROR"){
        ErrorFrame* frame = new ErrorFrame(vec);
        frame->setType(ERROR);
    }
    else{
        return nullptr;
    }
}
