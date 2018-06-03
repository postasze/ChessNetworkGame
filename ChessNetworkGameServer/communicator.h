#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <vector>
#include "constants.h"
#include <string>

class Controller;
class ClientHandler;

class Communicator
{
public:
    Communicator();

    int openCommunication();
    void acceptClientConnections();
    void closeCommunication();

    static void* listenToClient(void* arg);
    void writeReplyToClient(ClientHandler* clientHandler, std::string message);
    void writeReplyToManyClients(std::vector<ClientHandler*>& clientHandlers, std::string message);
    void setController(Controller *controller);

private:
    int serverSocketDescriptor;
    static Controller *controller;

};

#endif // COMMUNICATOR_H
