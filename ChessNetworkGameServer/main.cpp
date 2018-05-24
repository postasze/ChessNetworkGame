#include "controller.h"

int  main(int argc, char **argv)
{
    Controller controller;

    int result;

    if((result = controller.openCommunication()) != 0)
        return result;

    controller.acceptClientConnections();
    controller.closeCommunication();

    return 0;
}
