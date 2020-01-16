#include <string>
#include "Frame.h"

#ifndef BOOST_ECHO_CLIENT_CONNECTFRAME_H
#define BOOST_ECHO_CLIENT_CONNECTFRAME_H
using namespace std;

class ConnectFrame : public Frame{
private:

    string acceptVersion;
    string host;
    string login;
    string passcode;

public:
    ~ConnectFrame() override = default;
    const string &getLogin() const;
    explicit ConnectFrame(string&);
    string toString() override;
};

#endif //BOOST_ECHO_CLIENT_CONNECTFRAME_H

