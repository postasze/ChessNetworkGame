#include "clienthandler.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

ClientHandler::ClientHandler(int socketDescriptor, pthread_t pthreadId, std::string userName) :
    socketDescriptor(socketDescriptor), pthreadId(pthreadId), userName(userName)
{
    memset(inputBuffer, 0, BUFFER_SIZE);
    memset(outputBuffer, 0, BUFFER_SIZE);
}
