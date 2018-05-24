#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "communicator.h"
#include "clienthandler.h"

class ChessTable;

class Controller
{
public:
    Controller();

    int openCommunication();
    void acceptClientConnections();
    void closeCommunication();

    void createNewClientHandler(int fullAssociatedSocketDescriptor);
    void handleClientRequest(ClientHandler *clientHandler);
    void deleteClientHandler(ClientHandler *clientHandler);

private:
    Communicator communicator;
    std::vector<ClientHandler*> clientHandlers;
    std::vector<ChessTable*> chessTables;
    int currentChessTableID;
};

#endif // CONTROLLER_H
