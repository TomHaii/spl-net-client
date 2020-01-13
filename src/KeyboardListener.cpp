//
// Created by tomu@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "KeyboardListener.h"



bool KeyboardListener::isTerminate() const {
    return terminate;
}

void KeyboardListener::shouldTerminate() {
    terminate = true;
}

KeyboardListener::KeyboardListener(ConnectionHandler &_handler, StompProtocol &_stompProtocol):handler(_handler), stompProtocol(_stompProtocol),terminate(false) {

}

void KeyboardListener::operator()() {
    while(!terminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len = line.length();

        //build frame
        std::string frameMessage = stompProtocol.buildFrame(line)->toString();
        std::cout << "sending " + frameMessage << std::endl;
        //send full message
        if (!handler.sendLine(frameMessage)) {
            shouldTerminate();
            std::cout << "Disconnected. Exiting...\n" << std::endl;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;
    }
}
