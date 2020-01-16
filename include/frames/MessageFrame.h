#ifndef BOOST_ECHO_CLIENT_MESSAGEFRAME_H
#define BOOST_ECHO_CLIENT_MESSAGEFRAME_H

#include "Frame.h"

using namespace std;

class MessageFrame: public Frame {

private:
    string destination;
    string body;
public:
    ~MessageFrame() override;
    explicit MessageFrame(vector<string>&);
    const string &getDestination() const;
    string &getBody();
    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_MESSAGEFRAME_H
