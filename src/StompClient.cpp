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
    ConnectionHandler *handler;
    Client *client = nullptr;
    string inputLine;
    while (1) {
        std::cout << "please enter login info ";
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        inputLine = buf;
        string host;
        string tmpPort;
        bool dots = false;
        for (int i = 6; i < inputLine.size(); i++) {
            char c = inputLine.at(i);
            if (c == ':')
                dots = true;
            else if (c != ' ') {
                if (dots)
                    tmpPort += c;
                else
                    host += c;
            } else
                break;
        }

        std::cout << " sending new connect frame.. " << std::endl;
        short port = (short) stoi(tmpPort);
        handler = new ConnectionHandler(host, port);
        if (!handler->connect()) {
            std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
            std::cout << "Trying again.." << endl;
        } else
            break;
    }
    ConnectFrame frame(inputLine);
    handler->sendLine(frame.toString());
    string res;
    handler->getLine(res);
    Frame *frame1 = stompEncoderDecoder::decodeMessage(res);
    cout<<frame1->toString()<<endl;
    if (frame1->getType() == CONNECTED) {
        stompEncoderDecoder encoderDecoder;
        client = new Client(frame.getLogin());
        StompProtocol protocol(*handler, client);
        KeyboardListener keyboardListener(*handler, protocol);
        ServerListener serverListener(*handler,
                                      protocol, encoderDecoder);
        std::thread th1(std::ref(keyboardListener));
        std::thread th2(std::ref(serverListener));
        th1.join();
        th2.join();
    }
    return 0;
}


