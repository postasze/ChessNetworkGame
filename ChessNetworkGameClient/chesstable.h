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
    explicit ChessTable(QWidget *parent = 0, int chessTableId = 0);
    ~ChessTable();

    int chessTableId;

    Ui::ChessTable *ui;

private:
};

#endif // CHESSTABLE_H
