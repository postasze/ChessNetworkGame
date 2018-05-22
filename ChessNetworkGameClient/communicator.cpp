#include "communicator.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

int Communicator::socketDescriptor;
pthread_t Communicator::serverListenerThreadId;
char Communicator::inputBuffer[BUFFER_SIZE];
char Communicator::outputBuffer[BUFFER_SIZE];

Communicator::Communicator()
{
    memset(inputBuffer, 0, BUFFER_SIZE);
    memset(outputBuffer, 0, BUFFER_SIZE);
}

int Communicator::openCommunication(char *serverName, int portNumber)
{
    struct sockaddr_in server;
    struct hostent *hp;

    /* Create socket. */
    socketDescriptor = socket( AF_INET, SOCK_STREAM, 0 );
    if (socketDescriptor == -1) {
        perror("opening stream socket");
        return 1;
    }

    /* uzyskajmy adres IP z nazwy . */
    server.sin_family = AF_INET;
    hp = gethostbyname(serverName);

    /* hostbyname zwraca strukture zawierajaca adres danego hosta */
    if (hp == (struct hostent *) 0) {
        fprintf(stderr, "%s: unknown host\n", serverName);
        return 2;
    }
    memcpy((char *) &server.sin_addr, (char *) hp->h_addr,
        hp->h_length);
    server.sin_port = htons(portNumber);
    if (connect(socketDescriptor, (struct sockaddr *) &server, sizeof server)
        == -1) {
        perror("connecting stream socket");
        return 1;
    }

    pthread_create(&serverListenerThreadId, NULL, &listenToServer, NULL);

    return 0;
}

void* Communicator::listenToServer(void *arg)
{
    int returnValue;

    do
    {
        memset(inputBuffer, 0, BUFFER_SIZE);
        if ((returnValue = read(socketDescriptor, inputBuffer, BUFFER_SIZE)) == -1)
            perror("reading stream message");
        else if (returnValue == 0)
            printf("Ending connection\n");
        else
        {

        }
    }
    while (returnValue != 0);

    return 0;
}

void Communicator::closeCommunication()
{
    close(socketDescriptor);
}

