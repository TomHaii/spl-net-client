#include <stompEncoderDecoder.h>
#include <frames/ErrorFrame.h>


Frame *stompEncoderDecoder::decodeMessage(string &msg) {
    vector<string> vec;
    string word;
    for (char c: msg) {
        if (c == '\n') {
            if (!word.empty()) {
                vec.push_back(word);
                word = "";
            }
        } else
            word += c;
    }
    if (!word.empty())
        vec.push_back(word);
    if (!vec.empty()) {
        string type = vec.at(0);
        if (type == "CONNECTED") {
            auto *frame = new ConnectedFrame(vec);
            frame->setType(CONNECTED);
            return frame;
        } else if (type == "RECEIPT") {
            auto *frame = new ReceiptFrame(vec);
            frame->setType(RECEIPT);
            return frame;
        } else if (type == "MESSAGE") {
            auto *frame = new MessageFrame(vec);
            frame->setType(MESSAGE);
            return frame;
        } else if (type == "ERROR") {
            auto *frame = new ErrorFrame(vec,msg);
            frame->setType(ERROR);
            return frame;
        }
    }
    return nullptr;
}
