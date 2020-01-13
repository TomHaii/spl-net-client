#include <stdlib.h>
#include <thread>
#include <KeyboardListener.h>
#include <ServerListener.h>
//#include <connectionHandler.h>
#include "../include/connectionHandler.h"

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    //
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    else {
        StompProtocol stompProtocol = new StompProtocol(connectionHandler);
        stompEncoderDecoder encoderDecoder;
        KeyboardListener keyboardListener(connectionHandler, stompProtocol);
        ServerListener serverListener(connectionHandler, stompProtocol, encoderDecoder);

        std::cout << "finished initiating services" << std::endl;
        //From here we will see the rest of the ehco client implementation:
        std::cout << " waiting for terminate " << std::endl;
        std::thread th1(std::ref(keyboardListener));
        std::thread th2(std::ref(serverListener));
        th1.join();
        th2.join();
    }
    return 0;
}