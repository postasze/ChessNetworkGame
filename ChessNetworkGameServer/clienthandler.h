#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <pthread.h>
#include "constants.h"
#include <string>

class ClientHandler
{
public:
    ClientHandler(int socketDescriptor = 0, pthread_t pthreadId = 0, std::string userName = "");

    int socketDescriptor;
    pthread_t pthreadId;
    char inputBuffer[BUFFER_SIZE];
    char outputBuffer[BUFFER_SIZE];
    std::string userName;
};

#endif // CLIENTHANDLER_H
