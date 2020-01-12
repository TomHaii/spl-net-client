//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "SendFrame.h"

SendFrame::SendFrame():destination(""), body("") {
}

void SendFrame::buildSend(StompProtocol& stompProtocol ,string &str) {
    vector<string> vec = buildVector(str);
    string type = vec.at(0);
    string genre = vec.at(1);
    if(type == "status") {
        body = "book status";
    }
    else {
        string userName = stompProtocol.getUserName();
        string bookName = getBookName(vec);
        if (type == "add") {
            addCommend(stompProtocol, genre, userName, bookName);
        } else if (type == "borrow") {
            body = userName + " wish to borrow " + bookName;
        } else if (type == "return") {
            returnCommend(stompProtocol, genre, bookName);
        }
    }
    destination = genre;
}

string SendFrame::getBookName(vector<string> &vec) const {
    string bookName;
    for(unsigned long i = 2; i < vec.size(); i++){
        bookName.append(" " + vec.at(i));
    }
    return bookName;
}

void SendFrame::addCommend(StompProtocol &stompProtocol, string &genre, string &userName, string &bookName) {
    Book *book = new Book(genre, bookName, userName);
    if(stompProtocol.getBooksByGenre(genre) == nullptr){
        stompProtocol.getBooksMap()->at(genre) = new vector<Book>;
    }
    stompProtocol.addBook(*book);
    body = userName + " has added the book " + book->getBookName();
}

void SendFrame::returnCommend(StompProtocol &stompProtocol, string &genre, const string &bookName) {
    string borrowed;
    for (Book &book: *stompProtocol.getBooksByGenre(genre)) {
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

