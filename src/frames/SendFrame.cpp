#include "frames/SendFrame.h"
#include <iostream>
#include <utility>

SendFrame::SendFrame(Client& client, string& str):destination(""), body("") {
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
            client.getRequestedBooks()->at(destination).push_back(bookName);
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
    if(client.getBooksMap()->count(genre) == 0) {
        vector<Book> vec;
        vector<string> vec2;
        client.getBooksMap()->insert(pair<string, vector<Book>>(genre, vec));
        client.getRequestedBooks()->insert(pair<string, vector<string>>(genre, vec2));
    }
    bool exists = false;
    for (Book &b: client.getBooksByGenre(genre)) {
        if (b.getBookName() == bookName) {
            exists = true;
        }
    }
    if(!exists)
        client.addBook(book);
    body = userName + " has added the book " + book.getBookName();
}

void SendFrame::returnCommend(Client& client, string &genre, const string &bookName) {
    string borrowedFrom;
    if(client.getBooksMap()->count(genre)>0) {
        vector<Book> &booksList = client.getBooksByGenre(genre);
        for (auto it = booksList.begin(); it != booksList.end(); ++it) {
            Book b = *it;
            if (b.getBookName() == bookName) {
                borrowedFrom = b.getOwner();
                client.getBooksByGenre(genre).erase(it);
                break;
            }
        }
    }
    body = "Returning " + bookName + " to " + borrowedFrom;
}

string SendFrame::toString() {
    return "SEND\n"
           "destination:"+destination+"\n\n"+
           body+
           "\n";

}

SendFrame::SendFrame(string msg, string dest): body(std::move(msg)), destination(std::move(dest)){}

SendFrame::~SendFrame() {
    destination.clear();
    body.clear();
}

const string &SendFrame::getDestination() const {
    return destination;
}

