//
// Created by tomu@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "KeyboardListener.h"


KeyboardListener::KeyboardListener(ConnectionHandler &_handler, StompProtocol &_stompProtocol):handler(_handler), stompProtocol(_stompProtocol),terminate(false) {

}

void KeyboardListener::operator()() {
    while(!stompProtocol.shouldTerminate()) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len = line.length();
        //build frame
        Frame* frame =  stompProtocol.buildFrame(line);
        if (frame != nullptr) {
            std::string frameMessage = frame->toString();
            //send full message
            if (!handler.sendLine(frameMessage)) {
                stompProtocol.markAsTerminated();
                break;
            }
            // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
            std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;
            delete (frame);
        }
        if(line == "logout")
            break;
    }
}
