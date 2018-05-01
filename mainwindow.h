#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openNewChessTable();
    void activateSubWindow(QMdiSubWindow* qMdiSubWindow);
    void deleteChessTable(QObject* qObject);

private:
    void loadSubWindow(QWidget *widget, QString title);
    void removeSubWindow();

    Ui::MainWindow *ui;
    int currentChessTableID;
};

#endif // MAINWINDOW_H
