//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <Frame.h>
#include "StompProtocol.h"

void StompProtocol::process(Frame& frame) {

}

StompProtocol::~StompProtocol() {

}

StompProtocol::StompProtocol() {
    books = new vector<Book>();
}
