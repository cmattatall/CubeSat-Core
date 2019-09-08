//
// Created by Spencer Axford on 2019-05-15.
//

#ifndef LORIS_MESSAGERECEIVINGSERVICE_H
#define LORIS_MESSAGERECEIVINGSERVICE_H

#include "Message.h"
#include "DataMessage.h"
#include "UnixDomainStreamSocketServer.h"
#include "MessageRecipientInterface.h"


//A Messaging Service that allows for sending messages to a desiginated recipient 
class MessageReceivingService : protected MessageRecipientInterface {

public:
    //Constructor
    //identity is specified with Identifier int that specifies which system the messages are meant for (See Identifier.h)
    MessageReceivingService(unsigned int identifier);
    //Setter for Identifer after object construction
    void SetIdentifier( unsigned int identifier);
    
    //Method to start listening on a socket path for a client (must call once before ListenForMessage)
    int StartListeningForClients();

    //Method to listen for, and recieve a message
    int ListenForMessage(Message *&message) override;
    //Method to reply to last connected sender
    int Reply(Message &message) override;
    
private:
    UnixDomainStreamSocketServer server_socket_;
};

#endif //LORIS_MESSAGERECEIVINGSERVICE_H