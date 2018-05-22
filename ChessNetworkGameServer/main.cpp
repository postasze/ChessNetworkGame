#include "communicator.h"

int  main(int argc, char **argv)
{
    Communicator communicator;
    int result;

    if((result = communicator.openCommunication()) != 0)
        return result;

    communicator.acceptClientConnections();
    communicator.closeCommunication();

    return 0;
}
