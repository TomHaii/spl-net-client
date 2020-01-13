//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_FRAME_H
#define BOOST_ECHO_CLIENT_FRAME_H

#include <string>
#include <vector>

using namespace std;

enum FrameType{
    MESSAGE, CONNECTED, RECEIPT,OTHER, ERROR
};

class Frame {
protected:
    static vector<string> buildVector(string&);
public:
    FrameType type;

    virtual string toString() = 0;

    void setType(FrameType _type){
        type = _type;
    }

    FrameType getType(){
        return type;
    }

};


#endif //BOOST_ECHO_CLIENT_FRAME_H
