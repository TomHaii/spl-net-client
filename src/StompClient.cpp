#include <stdlib.h>
#include <thread>
#include <KeyboardListener.h>
#include <ServerListener.h>
//#include <connectionHandler.h>
#include "../include/connectionHandler.h"


void login(ConnectionHandler *&handler, string &inputLine);

void connect(ConnectionHandler *handler, Client *client, string &inputLine);

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
    ConnectionHandler *handler;
    Client *client = nullptr;
    string inputLine;
    login(handler, inputLine);
    connect(handler, client, inputLine);
    return 0;
}

void connect(ConnectionHandler *handler, Client *client, string &inputLine) {

    ConnectFrame frame(inputLine);
    handler->sendLine(frame.toString());
    string res;
    handler->getLine(res);
    Frame* frame1 = stompEncoderDecoder::decodeMessage(res);
    cout <<"\n"+ frame1->toString() << endl;
    if (frame1->getType() == CONNECTED) {
        cout << " MAKING LISTENERS ON MAIN " << endl;
        client = new Client(frame.getLogin());
        StompProtocol protocol(*handler, client);
        protocol.setConnected(true);
        KeyboardListener keyboardListener(*handler, protocol);
        ServerListener serverListener(*handler,
                                      protocol);
        thread th1(ref(keyboardListener));
        thread th2(ref(serverListener));
        //TODO: delete
//    delete (frame);
        th1.join();
        th2.join();
    }
    delete(&frame1);
    delete(&client);
}

void login(ConnectionHandler *&handler, string &inputLine) {
    while (1) {
        cout << "please enter login info ";
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
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
        cout << "Sending new connect frame.. " << endl;
        short port = (short) stoi(tmpPort);
        handler = new ConnectionHandler(host, port);
        if (!handler->connect()) {
            cerr << "Cannot connect to " << host << ":" << port << endl;
            cout << "Trying again.." << endl;
        } else {
            break;
        }
    }
}


