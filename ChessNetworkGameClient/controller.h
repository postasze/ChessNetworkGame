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

private slots:
    void loginDialogPushButtonClicked();
    void loginDialogFinished(int result);
    void createChessTablePushButtonClicked();
    void selectedChessTable(const QString& chessTableTitle);
    void joinChessTablePushButtonClicked();
    void removeChessTable(QObject* qObject);
    void createNewChessTable(int id);
    void handleReplyFromServer(QString messageFromServer);
    void chooseBlackColorSeatButtonClickedOnTable();
    void freeBlackColorSeatButtonClickedOnTable();
    void chooseWhiteColorSeatButtonClickedOnTable();
    void freeWhiteColorSeatButtonClickedOnTable();
    void startButtonClickedOnTable();
    void resignButtonClickedOnTable();
    void sendMessageButtonClickedOnTable();
    void playerFigurePressedOnTable(QPoint figurePosition);
    void playerHasMovedOnTable(QPoint figurePosition);

    void handleUsernameExistsReplyFromServer();
    void handleUsernameAcceptedReplyFromServer();
    void handleNewChessTableCreationReplyFromServer(int newChessTableId);
    void handleBlackSeatPlacementReplyFromServer(std::string message);
    void handleBlackSeatReleaseReplyFromServer(int chosenChessTableId);
    void handleWhiteSeatPlacementReplyFromServer(std::string message);
    void handleWhiteSeatReleaseReplyFromServer(int chosenChessTableId);
    void handleUserMessageDeliveryReplyFromServer(std::string message);
    void handleUserFigurePressReplyFromServer(std::string message);
    void handleUserFigureMoveReplyFromServer(std::string message);
    void handleStartGameReplyFromServer(int chosenChessTableId);
    void handleKingCheckReplyFromServer(int chosenChessTableId);
    void handleGameOverReplyFromServer(int chosenChessTableId);
    void handleChessTableDestructionReplyFromServer(int chosenChessTableId);

private:
    Communicator communicator;
    MainWindow mainWindow;
    LoginDialog loginDialog;
    QMessageBox qMessageBox;
    std::vector<ChessTable*> chessTables;
    QString userName;
    int currentlySelectedChessTableId;
};

#endif // CONTROLLER_H
