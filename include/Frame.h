//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_FRAME_H
#define BOOST_ECHO_CLIENT_FRAME_H

#include <string>
#include <vector>

using namespace std;

class Frame {
protected:
    static vector<string>& buildVector(string&);
public:
    virtual string toString() = 0;
};


#endif //BOOST_ECHO_CLIENT_FRAME_H
