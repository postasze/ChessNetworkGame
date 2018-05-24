#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Szachy");
    ui->mdiArea->setBackground(QBrush(QColor(200, 200, 200)));
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(activateSubWindow(QMdiSubWindow*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSubWindow(QWidget *widget)
{
    QMdiSubWindow* window = ui->mdiArea->addSubWindow(widget);
    //window->setWindowTitle(title);
    window->setWindowIcon(widget->windowIcon());
    window->resize(widget->width(), widget->height());
    //window->setWindowModality(Qt::WindowModal);
    window->show();
}

void MainWindow::removeSubWindow()
{
    this->ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::openChessTableWindow(ChessTable *chessTableWidget)
{
    loadSubWindow(chessTableWidget);
    ui->chessTablesListWidget->addItem(chessTableWidget->windowTitle());
}

void MainWindow::closeChessTableWindow(ChessTable *chessTableWidget)
{
    for(int i = 0; i < ui->chessTablesListWidget->count(); i++)
    {
        if (ui->chessTablesListWidget->item(i)->text() == QString("Stół szachowy nr: ") + QString::number(chessTableWidget->chessTableId))
            ui->chessTablesListWidget->takeItem(i);
    }
}

void MainWindow::activateSubWindow(QMdiSubWindow* qMdiSubWindow)
{

}
