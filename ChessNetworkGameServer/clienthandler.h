#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <pthread.h>
#include "constants.h"

class ClientHandler
{
public:
    ClientHandler(int socketDescriptor = 0, pthread_t pthreadId = 0);

    int socketDescriptor;
    pthread_t pthreadId;
    char inputBuffer[BUFFER_SIZE];
    char outputBuffer[BUFFER_SIZE];

    static void* handleClient(void* arg);
};

#endif // CLIENTHANDLER_H
