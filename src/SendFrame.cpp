//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "SendFrame.h"

SendFrame::SendFrame(string & str, Book& book) {
    vector<string> vec = buildVector(str);
    string type = vec.at(0);
    if(type == "add"){
        body = book.getOwner() + " has added the book " + book.getBookName();
    }
    else if (type == "borrow"){
        body =
    }
}
