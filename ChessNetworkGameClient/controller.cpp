#include "controller.h"
#include "ui_mainwindow.h"
#include "ui_logindialog.h"
#include "ui_chesstable.h"
#include <string>
#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent)
{
    connect(loginDialog.ui->loginPushButton, &QPushButton::clicked, this, &Controller::loginDialogPushButtonClicked);
    connect(&loginDialog, SIGNAL(finished(int)), this, SLOT(loginDialogFinished(int)));
    connect(mainWindow.ui->createTablePushButton, &QPushButton::clicked, this, &Controller::createChessTablePushButtonClicked);
    connect(mainWindow.ui->chessTablesListWidget, SIGNAL(currentTextChanged(QString)), this, SLOT(selectedChessTable(QString)));
    connect(mainWindow.ui->joinChessTablePushButton, &QPushButton::clicked, this, &Controller::joinChessTablePushButtonClicked);
    connect(&communicator, SIGNAL(replyFromServer(QString)), this, SLOT(handleReplyFromServer(QString)));

}

Controller::~Controller()
{
    foreach (ChessTable *chessTable, chessTables)
        delete chessTable;
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

void Controller::loginDialogPushButtonClicked()
{
    QString userName = loginDialog.ui->userNameLineEdit->text();

    if(!userName.isEmpty())
        communicator.sendMessageToServer("Username: " + userName.toStdString());
}

void Controller::loginDialogFinished(int result)
{
    if(result == QDialog::Rejected)
        mainWindow.close();
}

void Controller::createChessTablePushButtonClicked()
{
    communicator.sendMessageToServer("Create new chess table");
}

void Controller::selectedChessTable(const QString& chessTableTitle)
{
    currentlySelectedChessTableId = stoi(chessTableTitle.toStdString().substr(20, std::string::npos));
}

void Controller::joinChessTablePushButtonClicked()
{
    communicator.sendMessageToServer("Join chess table with id: " + std::to_string(currentlySelectedChessTableId));
}

void Controller::createNewChessTable(int id)
{
    chessTables.push_back(new ChessTable(&mainWindow, id));
    chessTables.back()->setWindowTitle(QString("Stół szachowy nr: ") + QString::number(id));
    mainWindow.openChessTableWindow(chessTables.back());
    connect(chessTables.back(), SIGNAL(destroyed(QObject*)), this, SLOT(deleteChessTable(QObject*)));
    connect(chessTables.back()->ui->choseBlackColorSeatButton, &QPushButton::clicked, this, &Controller::choseBlackColorSeatButtonClicked);
    connect(chessTables.back()->ui->freeBlackColorSeatButton, &QPushButton::clicked, this, &Controller::freeBlackColorSeatButtonClicked);
    connect(chessTables.back()->ui->choseWhiteColorSeatButton, &QPushButton::clicked, this, &Controller::choseWhiteColorSeatButtonClicked);
    connect(chessTables.back()->ui->freeWhiteColorSeatButton, &QPushButton::clicked, this, &Controller::freeWhiteColorSeatButtonClicked);
    connect(chessTables.back()->ui->startButton, &QPushButton::clicked, this, &Controller::startButtonClicked);
    connect(chessTables.back()->ui->resignButton, &QPushButton::clicked, this, &Controller::resignButtonClicked);
}

void Controller::deleteChessTable(QObject* qObject)
{
    ChessTable* chessTable = (ChessTable*) qObject;
    mainWindow.closeChessTableWindow(chessTable);
    chessTables.erase(std::find(chessTables.begin(), chessTables.end(), chessTable));
    delete chessTable;
}

void Controller::choseBlackColorSeatButtonClicked()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->choseBlackColorSeatButton == pressedButton;});

    communicator.sendMessageToServer("Chose black color seat button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::freeBlackColorSeatButtonClicked()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->freeBlackColorSeatButton == pressedButton;});

    communicator.sendMessageToServer("Free black color seat button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::choseWhiteColorSeatButtonClicked()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->choseWhiteColorSeatButton == pressedButton;});

    communicator.sendMessageToServer("Chose white color seat button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::freeWhiteColorSeatButtonClicked()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->freeWhiteColorSeatButton == pressedButton;});

    communicator.sendMessageToServer("Free white color seat button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::startButtonClicked()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->startButton == pressedButton;});

    communicator.sendMessageToServer("Start button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::resignButtonClicked()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->resignButton == pressedButton;});

    communicator.sendMessageToServer("Resign button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::handleReplyFromServer(QString messageFromServer)
{
    std::string message = messageFromServer.toStdString();

    if(message == "Username already exists")
    {
        qMessageBox.setWindowTitle("Wiadomość z serwera");
        qMessageBox.setText("Użytkownik o podanej nazwie już istnieje");
        qMessageBox.setModal(true);
        qMessageBox.show();
    }
    else if(message == "Username accepted")
    {
        this->userName = loginDialog.ui->userNameLineEdit->text();
        mainWindow.ui->usernameLabel->setText(this->userName);

        loginDialog.done(QDialog::Accepted);
    }
    else if(message.substr(0, 30) == "Chess table created with id = ")
        createNewChessTable(stoi(message.substr(30, std::string::npos)));
    else if(message.substr(0, 70) == "User has been placed on the seat with black figures on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(70, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

        chosenChessTable->ui->blackColorPlayerLabel->setText(userName);
    }
    else if(message.substr(0, 64) == "User has released the seat with black figures on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(64, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

        chosenChessTable->ui->blackColorPlayerLabel->setText("");
    }
    else if(message.substr(0, 70) == "User has been placed on the seat with white figures on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(70, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

        chosenChessTable->ui->whiteColorPlayerLabel->setText(userName);
    }
    else if(message.substr(0, 64) == "User has released the seat with white figures on table with id: ")
    {
        int chosenChessTableId = stoi(message.substr(64, std::string::npos));
        ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
            [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

        chosenChessTable->ui->whiteColorPlayerLabel->setText("");
    }
}
