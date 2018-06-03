#include "communicator.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <time.h>
#include "clienthandler.h"
#include "controller.h"

Controller *Communicator::controller;

Communicator::Communicator()
{

}

int Communicator::openCommunication()
{
    int length;
    struct sockaddr_in server;

    serverSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketDescriptor == -1) {
        perror("opening stream socket");
        return 1;
    }
    /* dowiaz adres do gniazda */

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 0;
    if (bind(serverSocketDescriptor, (struct sockaddr *) &server, sizeof server)
        == -1) {
        perror("binding stream socket");
        return 1;
    }
    /* wydrukuj na konsoli przydzielony port */
    length = sizeof( server);
    if (getsockname(serverSocketDescriptor,(struct sockaddr *) &server, (socklen_t*) &length)
         == -1) {
        perror("getting socket name");
        return 1;
    }
    printf("Socket port #%d\n", ntohs(server.sin_port));
    return 0;
}

void Communicator::acceptClientConnections()
{
    int fullAssociatedSocketDescriptor;

    /* zacznij przyjmowac polaczenia... */
    listen(serverSocketDescriptor, NUMBER_OF_QUEUED_CLIENTS);

    do {
        fullAssociatedSocketDescriptor = accept(serverSocketDescriptor,(struct sockaddr *) 0, (socklen_t*) 0);
        if (fullAssociatedSocketDescriptor == -1 )
             perror("accept");
        else
            controller->createNewClientHandler(fullAssociatedSocketDescriptor);

    } while(true);
    /*
     * gniazdo serverSocketDescriptor nie zostanie nigdy zamkniete jawnie,
     * jednak wszystkie deskryptory zostana zamkniete gdy proces
     * zostanie zakonczony (np w wyniku wystapienia sygnalu)
     */
}

// funkcja obslugujaca klienta
void* Communicator::listenToClient(void* arg)
{
    ClientHandler *clientHandler = (ClientHandler*) arg;
    int returnValue;

    do
    {
        memset(clientHandler->inputBuffer, 0, BUFFER_SIZE);
        if ((returnValue = read(clientHandler->socketDescriptor, clientHandler->inputBuffer, BUFFER_SIZE)) == -1)
            perror("reading stream message");
        else if (returnValue == 0)
        {
            printf("Ending connection\n");
            controller->deleteClientHandler(clientHandler);
        }
        else
            controller->handleClientRequest(clientHandler);
    }
    while (returnValue != 0);

    return 0;
}

void Communicator::writeReplyToClient(ClientHandler* clientHandler, std::string message)
{
    memset(clientHandler->outputBuffer, 0, BUFFER_SIZE);
    strcpy(clientHandler->outputBuffer, message.c_str());
    write(clientHandler->socketDescriptor, clientHandler->outputBuffer, BUFFER_SIZE);
}

void Communicator::writeReplyToManyClients(std::vector<ClientHandler*>& clientHandlers, std::string message)
{
    for(unsigned int i = 0; i < clientHandlers.size(); i++)
    {
        memset(clientHandlers[i]->outputBuffer, 0, BUFFER_SIZE);
        strcpy(clientHandlers[i]->outputBuffer, message.c_str());
        write(clientHandlers[i]->socketDescriptor, clientHandlers[i]->outputBuffer, BUFFER_SIZE);
    }
}

void Communicator::closeCommunication()
{
    close(serverSocketDescriptor);
}

void Communicator::setController(Controller *controller)
{
    this->controller = controller;
}
