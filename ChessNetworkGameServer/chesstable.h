#ifndef CHESSTABLE_H
#define CHESSTABLE_H

#include <vector>

class ClientHandler;

class ChessTable
{
public:
    ChessTable(int chessTableId = 0);

    int chessTableId;
    std::vector<ClientHandler*> clientsOnTable;
    ClientHandler *clientWithBlackFigures;
    ClientHandler *clientWithWhiteFigures;

private:

};

#endif // CHESSTABLE_H
