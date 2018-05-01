#include "chesstable.h"
#include "ui_chesstable.h"

ChessTable::ChessTable(QWidget *parent, int chessTableID) :
    QWidget(parent), chessTableID(chessTableID),
    ui(new Ui::ChessTable)
{
    ui->setupUi(this);
    this->setWindowTitle("Stół szachowy");
}

ChessTable::~ChessTable()
{
    delete ui;
}

