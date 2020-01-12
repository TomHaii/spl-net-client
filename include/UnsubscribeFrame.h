//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_UNSUBSCRIBEFRAME_H
#define BOOST_ECHO_CLIENT_UNSUBSCRIBEFRAME_H


#include "Frame.h"

using namespace std;
class UnsubscribeFrame: public Frame {
private:
    string destination;
    int id;
public:
    UnsubscribeFrame(string& str);

    int getId();
    void setId(int receipt);


    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_UNSUBSCRIBEFRAME_H
