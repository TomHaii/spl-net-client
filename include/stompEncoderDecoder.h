//
// Created by tomle on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
#define BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H

#include <vector>
#include <string>
#include <boost/asio.hpp>
#include "frame.h"


class stompEncoderDecoder{
private:
    std::vector<std::string> message;
    std::vector<char> bytes;
    int len;
public:
    frame decodeNextByte(char nextByte);

};


#endif //BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
