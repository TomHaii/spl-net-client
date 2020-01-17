#include "frames/SendFrame.h"
#include <iostream>
#include <utility>

SendFrame::SendFrame(Client& client, string& str):destination(""), body(str) {
    vector<string> vec = buildVector(str);
    string type = vec.at(0);
    string genre = vec.at(1);
    destination = genre;
    if(type == "status") {
        body = "Book status";
    }
    else {
        string userName = client.getUserName();
        string bookName = getBookName(vec);
        if (type == "add") {
            addCommend(client, genre, userName, bookName);
        } else if (type == "borrow") {
            client.requestBook(destination,bookName);
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
    bookName=bookName.substr(1);

    return bookName;
}

void SendFrame::addCommend(Client& client, string &genre, string &userName, string &bookName) {
    Book book(genre, bookName, userName);
    client.addBook(book, genre, bookName);
    body = userName + " has added the book " + book.getBookName();
}

void SendFrame::returnCommend(Client& client, string &genre, const string &bookName) {
    string borrowedFrom;
    client.returnBook(borrowedFrom, genre, bookName);
    body = "Returning " + bookName + " to " + borrowedFrom;
}

string SendFrame::toString() {
    return "SEND\n"
           "destination:"+destination+"\n\n"+
           body+
           "\n";

}

SendFrame::SendFrame(string msg, string dest): body(msg), destination(std::move(dest)){}

SendFrame::~SendFrame() {
    destination.clear();
    body.clear();
}

const string &SendFrame::getDestination() const {
    return destination;
}

