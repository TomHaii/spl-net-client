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
            vec.push_back(word);
            std::cout << "word " + word << std::endl;
            word = "";
        }
        else{
            word += c;
        }
    }
    vec.push_back(word);
    return vec;
}
