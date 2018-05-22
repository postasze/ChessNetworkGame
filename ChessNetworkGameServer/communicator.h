#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <vector>
#include "clienthandler.h"

class Communicator
{
public:
    Communicator();

    int openCommunication();
    void acceptClientConnections();
    void closeCommunication();

private:
    std::vector<ClientHandler*> clientHandlers;
    int serverSocketDescriptor;

};

#endif // COMMUNICATOR_H
