#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "constants.h"

class Communicator
{
public:
    Communicator();

    int openCommunication(char *serverName, int portNumber);
    void closeCommunication();

    static void* listenToServer(void *arg);

private:
    static int socketDescriptor;
    static pthread_t serverListenerThreadId;
    static char inputBuffer[BUFFER_SIZE];
    static char outputBuffer[BUFFER_SIZE];
};

#endif // COMMUNICATOR_H
