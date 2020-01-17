
#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H
#include <string>
#include <vector>
#include <unordered_map>
#include <frames/ReceiptFrame.h>
#include <mutex>


#include "Book.h"

using namespace std;

class Client {
private:
    unordered_map<string, vector<Book>> *booksMap;
    unordered_map<string, vector<string>> *requestedBooks;
    string name;
    int subscriptionId;
    int receiptId;
    unordered_map<int, string>* topicsSubscriptionsById;
    int disconnectReceipt = -1;
    unordered_map<int, bool> *receipts;

    mutex booksMap_lock;
    mutex requested_lock;
    mutex topics_lock;
    mutex receipts_lock;



public:
    Client();
    virtual ~Client();
    Client(const Client&);
    Client& operator = (const Client &t);
    unordered_map<int, string> *getTopicsSubscriptionsById();
    unordered_map<string, vector<string>> *getRequestedBooks();
    unordered_map<string, vector<Book>> *getBooksMap() const;
    int getSubscriptionIdByTopic(string& topic);
    bool getReceiptById(int id);
    void setName(const string &name);
    int getReceiptId() const;
    void incrementSubscriptionId();
    void incrementReceiptId();
    unordered_map<int, bool> *getReceipts();
    vector<Book>& getBooksByGenre(const string&);
    void addBook(const Book&, const string&, const string&);
    const string &getUserName() const;
    void setDisconnectReceipt(int _disconnectReceipt);
    int getDisconnectReceipt() const;
    void eraseReceipt(int _id);
    void eraseTopic(string& s);
    void setReceiptReceived(int id);
    void freeBook(const string& , string&);
    void acquireBook(const string& , string&);
    void addReceipt(int id);
    Frame* subscribe(const string& topic, Frame*, string&);
    bool letBorrow(const string& topic, string& book);
    string takeBook(string& topic, string& book, string& owner);
    string buildBooksList(const string& s);
    void requestBook(const string& topic, const string& book);
    void addBook(const Book &book);
    void returnBook(string& borrowedFrom, const string& topic, const string& bookName);
};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
