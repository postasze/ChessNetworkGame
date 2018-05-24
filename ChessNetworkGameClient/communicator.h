#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include "constants.h"

class Controller;

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);
    ~Communicator();

    int openCommunication(char *serverName, int portNumber);
    void sendMessageToServer(std::string message);
    void closeCommunication();

    static void* listenToServer(void *arg);

signals:
    void replyFromServer(QString message);

private:
    static int socketDescriptor;
    static pthread_t serverListenerThreadId;
    static char inputBuffer[BUFFER_SIZE];
    static char outputBuffer[BUFFER_SIZE];
};

#endif // COMMUNICATOR_H
