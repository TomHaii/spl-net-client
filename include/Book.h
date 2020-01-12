//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>

using namespace std;
class Book {
private:
    string bookName;
    string owner;
    string borrowedFrom;
public:
    Book(string&, string&, string&);
    const string &getBookName() const;

    const string &getOwner() const;

    const string &getBorrowedFrom() const;
};


#endif //BOOST_ECHO_CLIENT_BOOK_H
