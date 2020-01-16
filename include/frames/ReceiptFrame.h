#ifndef BOOST_ECHO_CLIENT_RECEIPTFRAME_H
#define BOOST_ECHO_CLIENT_RECEIPTFRAME_H


#include "Frame.h"

class ReceiptFrame: public Frame {
private:
    int id;
public:
    explicit ReceiptFrame(int _id);
    explicit ReceiptFrame(vector<string>&);
    ~ReceiptFrame() override = default;
    int getId() const;
    string toString() override;
};


#endif //BOOST_ECHO_CLIENT_RECEIPTFRAME_H
