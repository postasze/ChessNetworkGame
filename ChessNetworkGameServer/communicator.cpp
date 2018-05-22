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
        {
            clientHandlers.push_back(new ClientHandler(fullAssociatedSocketDescriptor));
            pthread_create(&clientHandlers.back()->pthreadId, NULL, &clientHandlers.back()->handleClient, (void*) clientHandlers.back());
        }
    } while(true);
    /*
     * gniazdo serverSocketDescriptor nie zostanie nigdy zamkniete jawnie,
     * jednak wszystkie deskryptory zostana zamkniete gdy proces
     * zostanie zakonczony (np w wyniku wystapienia sygnalu)
     */
}

void Communicator::closeCommunication()
{
    close(serverSocketDescriptor);
}
