#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "communicator.h"
#include "mainwindow.h"
#include "chesstable.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    int openCommunication(char *serverName, int portNumber);
    void run();
    void closeCommunication();

signals:

private slots:
    void userLoggedIn(QString userName);
    void loginDialogFinished(int result);
    void createNewChessTable();
    void deleteChessTable(QObject* qObject);

private:
    Communicator communicator;
    MainWindow mainWindow;
    LoginDialog loginDialog;
    std::vector<ChessTable*> chessTables;
    QString userName;
    int currentChessTableID;
};

#endif // CONTROLLER_H
