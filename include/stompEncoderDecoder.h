//
// Created by tomle on 10/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
#define BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H

#include <vector>
#include <string>
#include <boost/asio.hpp>
#include "Frame.h"


class stompEncoderDecoder{
private:

public:
    const Frame& buildFrame(std::string& message);

};


#endif //BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
