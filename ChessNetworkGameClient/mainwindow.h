#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "logindialog.h"
#include "communicator.h"
#include "chesstable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
    void openChessTableWindow(ChessTable* chessTableWidget);
    void closeChessTableWindow(ChessTable *chessTableWidget);

private slots:
    void activateSubWindow(QMdiSubWindow* qMdiSubWindow);

private:
    void loadSubWindow(QWidget *widget);
    void removeSubWindow();
};

#endif // MAINWINDOW_H
