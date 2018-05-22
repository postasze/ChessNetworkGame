#include "mainwindow.h"
#include "controller.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    int result;

    if(argc != 3)
    {
        std::cout << "Usage:" << argv[0] << "<ip of server> <port number>" << std::endl;
        return 1;
    }

    if((result = controller.openCommunication(argv[1], atoi(argv[2]))) != 0)
        return result;

    controller.run();

    result = a.exec();
    controller.closeCommunication();
    return result;
}
