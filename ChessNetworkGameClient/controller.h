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
    void deleteChessTable(QObject* qObject);
    void createNewChessTable(int id);
    void handleReplyFromServer(QString messageFromServer);
    void choseBlackColorSeatButtonClicked();
    void freeBlackColorSeatButtonClicked();
    void choseWhiteColorSeatButtonClicked();
    void freeWhiteColorSeatButtonClicked();
    void startButtonClicked();
    void resignButtonClicked();

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
