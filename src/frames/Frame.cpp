//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <iostream>
#include "frames/Frame.h"

vector<string> Frame::buildVector(string & s) {
    string word;
    vector<string> vec;
    for (char c : s){
        if(c == ' ') {
            if(!word.empty()) {
                vec.push_back(word);
                word = "";
            }
        }
        else{
            word += c;
        }
    }
    if(!word.empty())
        vec.push_back(word);
    return vec;
}
