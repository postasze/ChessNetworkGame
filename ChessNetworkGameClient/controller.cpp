#include "controller.h"
#include "ui_mainwindow.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    connect(&loginDialog, SIGNAL(userLoggedIn(QString)), this, SLOT(userLoggedIn(QString)));
    connect(&loginDialog, SIGNAL(finished(int)), this, SLOT(loginDialogFinished(int)));
    connect(mainWindow.ui->createTablePushButton, &QPushButton::clicked, this, &Controller::createNewChessTable);

    currentChessTableID = 0;
}

Controller::~Controller()
{
    foreach (ChessTable *chessTable, chessTables)
    {
        delete chessTable;
    }
    chessTables.clear();
}

int Controller::openCommunication(char *serverName, int portNumber)
{
    return communicator.openCommunication(serverName, portNumber);
}

void Controller::run()
{
    mainWindow.showMaximized();

    loginDialog.setModal(true);
    loginDialog.show();
}

void Controller::closeCommunication()
{
    communicator.closeCommunication();
}

void Controller::createNewChessTable()
{
    chessTables.push_back(new ChessTable(&mainWindow, currentChessTableID));
    chessTables.back()->setWindowTitle(QString("Stół szachowy nr: ") + QString::number(currentChessTableID));
    mainWindow.openChessTableWindow(chessTables.back());
    connect(chessTables.back(), SIGNAL(destroyed(QObject*)), this, SLOT(deleteChessTable(QObject*)));
    currentChessTableID++;
}

void Controller::deleteChessTable(QObject* qObject)
{
    ChessTable* chessTable = (ChessTable*) qObject;
    mainWindow.closeChessTableWindow(chessTable);
}

void Controller::userLoggedIn(QString userName)
{
    this->userName = userName;
}

void Controller::loginDialogFinished(int result)
{
    if(result == QDialog::Rejected)
    {
        mainWindow.close();
    }
}
