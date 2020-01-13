//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "Book.h"

const string &Book::getBookName() const {
    return bookName;
}

const string &Book::getOwner() const {
    return owner;
}


Book::Book(string& _genre, string & _bookName, string & _owner):genre(_genre),bookName(_bookName), owner(_owner), available(true) {
}



const string &Book::getGenre() const {
    return genre;
}

void Book::free() {
    available = true;
}

void Book::acquire() {
    available = false;

}

bool Book::isAvailable() const {
    return available;
}
