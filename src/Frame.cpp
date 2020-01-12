//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "Frame.h"

vector<string> &Frame::buildVector(string & s) {
    string word = "";
    vector<string> vec;
    for (char c : s){
        if(c == ' ') {
            vec.push_back(word);
            word = "";
        }
        else{
            word += c;
        }
    }
    return vec;
}
