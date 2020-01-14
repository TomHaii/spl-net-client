//
// Created by tomu@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "ServerListener.h"


ServerListener::ServerListener(ConnectionHandler &_connectionHandler, StompProtocol &_stompProtocol,
                               stompEncoderDecoder &_stompEncoderDecoder):connectionHandler(_connectionHandler), stompProtocol(_stompProtocol), stompEncDec(_stompEncoderDecoder), terminate(false) {
}

void ServerListener::shouldTerminate() {
    terminate = true;
}

bool ServerListener::isTerminate() const {
    return terminate;
}

void ServerListener::operator()() {
    while(!terminate) {
        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end

        if (!connectionHandler.getLine(answer)) {
            shouldTerminate();
            std::cout << "Disconnected. Exiting...\n" << std::endl;
        }
        //TODO: DELETE ENCODERDECODER FROM THE CONSTRUCTOR
        Frame *frame = stompEncoderDecoder::decodeMessage(answer);
        stompProtocol.process(frame);
        std::cout << frame->toString() << std::endl;
        int len = answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len - 1);
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            shouldTerminate();
            std::cout << "Exiting...\n" << std::endl;
        }
    }
}

void run(){

}
