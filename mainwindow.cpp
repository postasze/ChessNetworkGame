#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chesstable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Szachy");
    ui->mdiArea->setBackground(QBrush(QColor(200, 200, 200)));
    connect(ui->createTablePushButton, &QPushButton::clicked, this, &MainWindow::openNewChessTable);
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(activateSubWindow(QMdiSubWindow*)));

    currentChessTableID = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadSubWindow(QWidget *widget, QString title)
{
    QMdiSubWindow* window = ui->mdiArea->addSubWindow(widget);
    window->setWindowTitle(title);
    window->setWindowIcon(widget->windowIcon());
    window->resize(widget->width(), widget->height());
    //window->setWindowModality(Qt::WindowModal);
    window->show();
}

void MainWindow::removeSubWindow()
{
    this->ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::openNewChessTable()
{
    ChessTable *newChessTable = new ChessTable(this, currentChessTableID++);
    QString windowTitle = QString("Stół szachowy nr: ") + QString::number(newChessTable->chessTableID);
    loadSubWindow(newChessTable, windowTitle);
    ui->chessTablesListWidget->addItem(windowTitle);
    connect(newChessTable, SIGNAL(destroyed(QObject*)), this, SLOT(deleteChessTable(QObject*)));
}

void MainWindow::activateSubWindow(QMdiSubWindow* qMdiSubWindow)
{

}

void MainWindow::deleteChessTable(QObject* qObject)
{
    ChessTable* chessTable = (ChessTable*) qObject;
    for(int i = 0; i < ui->chessTablesListWidget->count(); i++)
    {
        if (ui->chessTablesListWidget->item(i)->text() == QString("Stół szachowy nr: ") + QString::number(chessTable->chessTableID))
            ui->chessTablesListWidget->takeItem(i);
    }
}
