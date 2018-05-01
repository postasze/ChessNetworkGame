#ifndef CHESSTABLE_H
#define CHESSTABLE_H

#include <QWidget>

namespace Ui {
class ChessTable;
}

class ChessTable : public QWidget
{
    Q_OBJECT

public:
    explicit ChessTable(QWidget *parent = 0, int chessTableID = 0);
    ~ChessTable();

    int chessTableID;

private:
    Ui::ChessTable *ui;
};

#endif // CHESSTABLE_H
