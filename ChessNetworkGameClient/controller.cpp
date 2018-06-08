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

    currentlySelectedChessTableId = -1;
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

    if(userName.isEmpty())
        return;

    if(userName.toStdString().find(' ') != std::string::npos)
    {
        qMessageBox.setWindowTitle("Wiadomość z aplikacji");
        qMessageBox.setText("Nazwa użytkownika nie powinna zawierać spacji");
        qMessageBox.setModal(true);
        qMessageBox.show();
    }
    else
        communicator.sendMessageToServer("New client with username: " + userName.toStdString());
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
    if(mainWindow.ui->chessTablesListWidget->count() == 0)
        return;

    if(currentlySelectedChessTableId == -1)
        return;

    communicator.sendMessageToServer("Join chess table with id: " + std::to_string(currentlySelectedChessTableId));
}

void Controller::createNewChessTable(int id)
{
    chessTables.push_back(new ChessTable(&mainWindow, id));
    chessTables.back()->setWindowTitle(QString("Stół szachowy nr: ") + QString::number(id));
    mainWindow.openChessTableWindow(chessTables.back());
    connect(chessTables.back(), SIGNAL(destroyed(QObject*)), this, SLOT(removeChessTable(QObject*)));
    connect(chessTables.back()->ui->choseBlackColorSeatButton, &QPushButton::clicked, this, &Controller::chooseBlackColorSeatButtonClickedOnTable);
    connect(chessTables.back()->ui->freeBlackColorSeatButton, &QPushButton::clicked, this, &Controller::freeBlackColorSeatButtonClickedOnTable);
    connect(chessTables.back()->ui->choseWhiteColorSeatButton, &QPushButton::clicked, this, &Controller::chooseWhiteColorSeatButtonClickedOnTable);
    connect(chessTables.back()->ui->freeWhiteColorSeatButton, &QPushButton::clicked, this, &Controller::freeWhiteColorSeatButtonClickedOnTable);
    connect(chessTables.back()->ui->startButton, &QPushButton::clicked, this, &Controller::startButtonClickedOnTable);
    connect(chessTables.back()->ui->resignButton, &QPushButton::clicked, this, &Controller::resignButtonClickedOnTable);
    connect(chessTables.back()->ui->sendMessageButton, &QPushButton::clicked, this, &Controller::sendMessageButtonClickedOnTable);
    connect(chessTables.back()->ui->chessGameWidget, SIGNAL(playerFigurePressed(QPoint)), this, SLOT(playerFigurePressedOnTable(QPoint)));
    connect(chessTables.back()->ui->chessGameWidget, SIGNAL(playerHasMoved(QPoint)), this, SLOT(playerHasMovedOnTable(QPoint)));
}

void Controller::removeChessTable(QObject* qObject)
{
    ChessTable* chessTable = (ChessTable*) qObject;
    chessTables.erase(std::find(chessTables.begin(), chessTables.end(), chessTable));
}

void Controller::chooseBlackColorSeatButtonClickedOnTable()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->choseBlackColorSeatButton == pressedButton;});

    communicator.sendMessageToServer("Choose black color seat button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::freeBlackColorSeatButtonClickedOnTable()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->freeBlackColorSeatButton == pressedButton;});

    communicator.sendMessageToServer("Free black color seat button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::chooseWhiteColorSeatButtonClickedOnTable()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->choseWhiteColorSeatButton == pressedButton;});

    communicator.sendMessageToServer("Choose white color seat button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::freeWhiteColorSeatButtonClickedOnTable()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->freeWhiteColorSeatButton == pressedButton;});

    communicator.sendMessageToServer("Free white color seat button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::startButtonClickedOnTable()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->startButton == pressedButton;});

    communicator.sendMessageToServer("Start button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::resignButtonClickedOnTable()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->resignButton == pressedButton;});

    communicator.sendMessageToServer("Resign button clicked by client on table with id: " + std::to_string(chosenChessTable->chessTableId));
}

void Controller::sendMessageButtonClickedOnTable()
{
    QPushButton *pressedButton = (QPushButton*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [pressedButton](ChessTable *chessTable) {return chessTable->ui->sendMessageButton == pressedButton;});

    if(chosenChessTable->ui->messageLineEdit->text() == "")
        return;

    communicator.sendMessageToServer("User has sent message on chess table with id: " + std::to_string(chosenChessTable->chessTableId) + " " + chosenChessTable->ui->messageLineEdit->text().toStdString());
}

void Controller::playerFigurePressedOnTable(QPoint figurePosition)
{
    ChessGameWidget *chosenChessGame = (ChessGameWidget*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessGame](ChessTable *chessTable) {return chessTable->ui->chessGameWidget == chosenChessGame;});

    communicator.sendMessageToServer("User has pressed his figure on chess table with id: " + std::to_string(chosenChessTable->chessTableId) + " " + std::to_string(figurePosition.x()) + " " + std::to_string(figurePosition.y()));
}

void Controller::playerHasMovedOnTable(QPoint figurePosition)
{
    ChessGameWidget *chosenChessGame = (ChessGameWidget*) QObject::sender();
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessGame](ChessTable *chessTable) {return chessTable->ui->chessGameWidget == chosenChessGame;});

    communicator.sendMessageToServer("User has moved his figure on chess table with id: " + std::to_string(chosenChessTable->chessTableId) + " " + std::to_string(figurePosition.x()) + " " + std::to_string(figurePosition.y()));
}

void Controller::handleReplyFromServer(QString messageFromServer)
{
    std::string message = messageFromServer.toStdString();

    if(message == "Username already exists")
        handleUsernameExistsReplyFromServer();
    else if(message == "Username accepted")
        handleUsernameAcceptedReplyFromServer();
    else if(message.substr(0, 30) == "Chess table created with id = ")
        handleNewChessTableCreationReplyFromServer(stoi(message.substr(30, std::string::npos)));
    else if(message.substr(0, 32) == "Joined to chess table with id = ")
        createNewChessTable(stoi(message.substr(32, std::string::npos)));
    else if(message.substr(0, 70) == "User has been placed on the seat with black figures on table with id: ")
        handleBlackSeatPlacementReplyFromServer(message.substr(70, std::string::npos));
    else if(message.substr(0, 64) == "User has released the seat with black figures on table with id: ")
        handleBlackSeatReleaseReplyFromServer(stoi(message.substr(64, std::string::npos)));
    else if(message.substr(0, 70) == "User has been placed on the seat with white figures on table with id: ")
        handleWhiteSeatPlacementReplyFromServer(message.substr(70, std::string::npos));
    else if(message.substr(0, 64) == "User has released the seat with white figures on table with id: ")
        handleWhiteSeatReleaseReplyFromServer(stoi(message.substr(64, std::string::npos)));
    else if(message.substr(0, 46) == "User has sent message on chess table with id: ")
        handleUserMessageDeliveryReplyFromServer(message.substr(46, std::string::npos));
    else if(message.substr(0, 46) == "Possible moves points on chess table with id: ")
        handleUserFigurePressReplyFromServer(message.substr(46, std::string::npos));
    else if(message.substr(0, 50) == "User has moved his figure on chess table with id: ")
        handleUserFigureMoveReplyFromServer(message.substr(50, std::string::npos));
    else if(message.substr(0, 35) == "Game has started on table with id: ")
        handleStartGameReplyFromServer(stoi(message.substr(35, std::string::npos)));
    else if(message.substr(0, 40) == "King is checked on chess table with id: ")
        handleKingCheckReplyFromServer(stoi(message.substr(40, std::string::npos)));
}

void Controller::handleUsernameExistsReplyFromServer()
{
    qMessageBox.setWindowTitle("Wiadomość z serwera");
    qMessageBox.setText("Użytkownik o podanej nazwie już istnieje");
    qMessageBox.setModal(true);
    qMessageBox.show();
}

void Controller::handleUsernameAcceptedReplyFromServer()
{
    this->userName = loginDialog.ui->userNameLineEdit->text();
    mainWindow.ui->usernameLabel->setText(this->userName);

    loginDialog.done(QDialog::Accepted);
}

void Controller::handleNewChessTableCreationReplyFromServer(int newChessTableId)
{
    mainWindow.addNewChessTableLabelToListWidget(QString("Stół szachowy nr: ") + QString::number(newChessTableId));
}

void Controller::handleBlackSeatPlacementReplyFromServer(std::string message)
{
    std::size_t spacePosition = message.find(' ');
    int chosenChessTableId = stoi(message.substr(0, spacePosition));
    std::string seatedUserName = message.substr(spacePosition + 1, std::string::npos);

    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->blackColorPlayerLabel->setText(QString::fromStdString(seatedUserName));
    if(QString::fromStdString(seatedUserName) == this->userName)
        chosenChessTable->ui->chessGameWidget->playerColor = PlayerColor::Black;
}

void Controller::handleBlackSeatReleaseReplyFromServer(int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->blackColorPlayerLabel->setText("");
    if (chosenChessTable->ui->chessGameWidget->playerColor == PlayerColor::Black)
        chosenChessTable->ui->chessGameWidget->playerColor = PlayerColor::None;
}

void Controller::handleWhiteSeatPlacementReplyFromServer(std::string message)
{
    std::size_t spacePosition = message.find(' ');
    int chosenChessTableId = stoi(message.substr(0, spacePosition));
    std::string seatedUserName = message.substr(spacePosition + 1, std::string::npos);

    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->whiteColorPlayerLabel->setText(QString::fromStdString(seatedUserName));
    if(QString::fromStdString(seatedUserName) == this->userName)
        chosenChessTable->ui->chessGameWidget->playerColor = PlayerColor::White;
}

void Controller::handleWhiteSeatReleaseReplyFromServer(int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->whiteColorPlayerLabel->setText("");
    if (chosenChessTable->ui->chessGameWidget->playerColor == PlayerColor::White)
        chosenChessTable->ui->chessGameWidget->playerColor = PlayerColor::None;
}

void Controller::handleUserMessageDeliveryReplyFromServer(std::string message)
{
    std::size_t spacePosition;

    spacePosition = message.find(' ');
    int chosenChessTableId = stoi(message.substr(0, spacePosition));
    message.erase(0, spacePosition + 1);
    spacePosition = message.find(' ');
    std::string nameOfUserSendingMessage = message.substr(0, spacePosition);
    std::string userMessage = message.substr(spacePosition + 1, std::string::npos);

    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->communicationBoxPlainTextEdit->setPlainText(chosenChessTable->ui->communicationBoxPlainTextEdit->toPlainText() + QString::fromStdString(nameOfUserSendingMessage) + ":" + QString::fromStdString(userMessage) + "\n");
}

void Controller::handleUserFigurePressReplyFromServer(std::string message)
{
    std::vector<QPoint> possibleMoves;
    std::size_t spacePosition;
    QPoint possibleMove;

    spacePosition = message.find(' ');
    int chosenChessTableId = stoi(message.substr(0, spacePosition));
    message.erase(0, spacePosition + 1);
    spacePosition = message.find(' ');

    while(spacePosition != std::string::npos)
    {
        possibleMove.setX(stoi(message.substr(0, spacePosition)));
        message.erase(0, spacePosition + 1);
        spacePosition = message.find(' ');
        possibleMove.setY(stoi(message.substr(0, spacePosition)));
        message.erase(0, spacePosition + 1);
        spacePosition = message.find(' ');
        possibleMoves.push_back(possibleMove);
    }

    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->chessGameWidget->possibleMoves = possibleMoves;
    chosenChessTable->ui->chessGameWidget->createPossibleMoveSquares(possibleMoves);
}

void Controller::handleUserFigureMoveReplyFromServer(std::string message)
{
    std::size_t spacePosition;
    QPoint startPoint, destinationPoint;

    spacePosition = message.find(' ');
    int chosenChessTableId = stoi(message.substr(0, spacePosition));
    message.erase(0, spacePosition + 1);
    spacePosition = message.find(' ');
    startPoint.setX(stoi(message.substr(0, spacePosition)));
    message.erase(0, spacePosition + 1);
    spacePosition = message.find(' ');
    startPoint.setY(stoi(message.substr(0, spacePosition)));
    message.erase(0, spacePosition + 1);
    spacePosition = message.find(' ');
    destinationPoint.setX(stoi(message.substr(0, spacePosition)));
    destinationPoint.setY(stoi(message.substr(spacePosition + 1, std::string::npos)));

    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->chessGameWidget->makeMove(startPoint, destinationPoint);
}

void Controller::handleStartGameReplyFromServer(int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->chessGameWidget->inGame = true;
}

void Controller::handleKingCheckReplyFromServer(int chosenChessTableId)
{
    ChessTable *chosenChessTable = *std::find_if(chessTables.begin(), chessTables.end(),
        [chosenChessTableId](ChessTable *chessTable) {return chessTable->chessTableId == chosenChessTableId;});

    chosenChessTable->ui->communicationBoxPlainTextEdit->setPlainText(chosenChessTable->ui->communicationBoxPlainTextEdit->toPlainText() + QString::fromStdString("Krol jest szachowany") + "\n");
}
