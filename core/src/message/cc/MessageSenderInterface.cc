//
// Created by Spencer Axford on 2019-05-15.
//

#include "MessageSenderInterface.h"

MessageSenderInterface::MessageSenderInterface(unsigned int recipient):
    MessagingService(recipient) {}

void MessageSenderInterface::SetRecipient(unsigned int recipient){
    std::string path = IdentifierToProcessFilePath(recipient);
    client_socket_ = UnixDomainStreamSocketClient(path);
}

int MessageSenderInterface::SendFlattenedMessage(char message[]) {
    return client_socket_.Send(message);
}

int MessageSenderInterface::SendMessage(Message message) {
    char msg[255] = "";
    message.flatten(msg);
    return SendFlattenedMessage(msg);
}

