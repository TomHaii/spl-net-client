//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>

using namespace std;
class Book {
private:
    string genre;
    string bookName;
    string owner;bool available;
public:
    bool isAvailable() const;

public:
    Book(string&, string&, string&);
    const string &getBookName() const;

    const string &getOwner() const;

    const string &getGenre() const;

    void free();

    void acquire();

    void setOwner(string &name);
};


#endif //BOOST_ECHO_CLIENT_BOOK_H
