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

const string &Book::getBorrowedFrom() const {
    return borrowedFrom;
}

Book::Book(string & _bookName, string & _owner, string & _borrowedFrom):bookName(_bookName), owner(_owner), borrowedFrom(_borrowedFrom) {
}
