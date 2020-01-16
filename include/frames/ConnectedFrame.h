#ifndef BOOST_ECHO_CLIENT_CONNECTEDFRAME_H
#define BOOST_ECHO_CLIENT_CONNECTEDFRAME_H

#include <string>
#include "Frame.h"

using namespace std;
class ConnectedFrame: public Frame{
private:
    string version;
public:
    ConnectedFrame():version("") {}
    ~ConnectedFrame() override;
    explicit ConnectedFrame(vector<string>&);
    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_CONNECTEDFRAME_H
