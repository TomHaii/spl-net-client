//
// Created by tomu@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "MessageFrame.h"

int MessageFrame::getSubscriptionId() const {
    return subscriptionId;
}

int MessageFrame::getMessageId() const {
    return messageId;
}

const string &MessageFrame::getDestination() const {
    return destination;
}

const string &MessageFrame::getBody() const {
    return body;
}

MessageFrame::MessageFrame(int subscriptionId, int messageId, const string &destination, const string &body)
        : subscriptionId(subscriptionId), messageId(messageId), destination(destination), body(body) {}
