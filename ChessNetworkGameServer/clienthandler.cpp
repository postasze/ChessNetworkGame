#include "clienthandler.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

ClientHandler::ClientHandler(int socketDescriptor, pthread_t pthreadId) :
    socketDescriptor(socketDescriptor), pthreadId(pthreadId)
{
    memset(inputBuffer, 0, BUFFER_SIZE);
    memset(outputBuffer, 0, BUFFER_SIZE);
}

// funkcja obslugujaca klienta
void* ClientHandler::handleClient(void* arg)
{
    ClientHandler *clientHandler = (ClientHandler*) arg;
    int returnValue;

    do
    {
        memset(clientHandler->inputBuffer, 0, BUFFER_SIZE);
        if ((returnValue = read(clientHandler->socketDescriptor, clientHandler->inputBuffer, BUFFER_SIZE)) == -1)
            perror("reading stream message");
        else if (returnValue == 0)
            printf("Ending connection\n");
        else
        {

        }
    }
    while (returnValue != 0);
}
