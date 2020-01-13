//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "frames/SendFrame.h"

SendFrame::SendFrame(Client& client, string& str):destination(""), body("") {
    vector<string> vec = buildVector(str);
    string type = vec.at(0);
    string genre = vec.at(1);
    destination = genre;

    if(type == "status") {
        body = "book status";
    }
    else {
        string userName = client.getUserName();
        string bookName = getBookName(vec);
        if (type == "add") {
            addCommend(client, genre, userName, bookName);
        } else if (type == "borrow") {
            body = userName + " wish to borrow " + bookName;
        } else if (type == "return") {
            returnCommend(client, genre, bookName);
        }
    }
}


string SendFrame::getBookName(vector<string> &vec) const {
    string bookName;
    for(unsigned long i = 2; i < vec.size(); i++){
        bookName.append(" " + vec.at(i));
    }
    return bookName;
}

void SendFrame::addCommend(Client& client, string &genre, string &userName, string &bookName) {
    Book *book = new Book(genre, bookName, userName);
    if(client.getBooksByGenre(genre) == nullptr){
        client.getBooksMap()->at(genre) = new vector<Book>;
    }
    client.addBook(*book);
    body = userName + " has added the book " + book->getBookName();
}

void SendFrame::returnCommend(Client& client, string &genre, const string &bookName) {
    string borrowed;
    for (Book &book: *client.getBooksByGenre(genre)) {
        if (book.getBookName() == bookName) {
            borrowed = book.getBorrowedFrom();
        }
    }
    body = "Returning " + bookName + " to " + borrowed;
}

const string &SendFrame::getDestination() const {
    return destination;
}

const string &SendFrame::getBody() const {
    return body;
}

string SendFrame::toString() {
    return "SEND\ndestination:"+destination+'\n'+body+'\n'+'\u0000';

}

