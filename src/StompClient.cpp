#include <stdlib.h>
#include <thread>
#include <KeyboardListener.h>
#include <ServerListener.h>


void login(ConnectionHandler &handler, string &inputLine);

void connect(ConnectionHandler &handler, Client &client, string &inputLine);

void connectedSuccessfully(ConnectionHandler &handler, Client &client, const ConnectFrame &frame);

void parseLoginInfo(string &inputLine, string &tmpPort, string &host);


/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
    ConnectionHandler handler;
    Client client;
    string inputLine;
    login(handler, inputLine);
    connect(handler, client, inputLine);
    return 0;
}

void connect(ConnectionHandler &handler, Client &client, string &inputLine) {
    ConnectFrame frame(inputLine);
    handler.sendLine(frame.toString());
    string res;
    handler.getLine(res);
    Frame* frame1 = stompEncoderDecoder::decodeMessage(res);
    cout <<"\n"+ frame1->toString() << endl;
    if (frame1->getType() == CONNECTED) {
        connectedSuccessfully(handler, client, frame);
    }
    delete(frame1);

}

void connectedSuccessfully(ConnectionHandler &handler, Client &client, const ConnectFrame &frame) {
    client.setName(frame.getLogin());
    StompProtocol protocol(handler, client);
    KeyboardListener keyboardListener(handler, protocol);
    ServerListener serverListener(handler,
                                  protocol);
    thread th1(ref(keyboardListener));
    thread th2(ref(serverListener));
    th1.join();
    th2.join();
}

void login(ConnectionHandler &handler, string &inputLine) {
    while (1) {
        cout << "please enter login info ";
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        inputLine = buf;
        string host;
        string tmpPort;
        parseLoginInfo(inputLine,tmpPort,host);
        cout << "Sending new connect frame.. " << endl;
        short port = (short) stoi(tmpPort);
        handler.setHost(host);
        handler.setPort(port);
        if (!handler.connect()) {
            cerr << "Cannot connect to " << host << ":" << port << endl;
            cout << "Trying again.." << endl;
        } else {
            break;
        }
    }
}

void parseLoginInfo(string &inputLine, string &tmpPort, string &host){
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
}




