#ifndef CHESSTABLE_H
#define CHESSTABLE_H

#include <vector>
#include "chessmatch.h"

class ClientHandler;

class ChessTable
{
public:
    ChessTable(int chessTableId = 0);

    int chessTableId;
    std::vector<ClientHandler*> clientsOnTable;
    ClientHandler *clientWithBlackFigures;
    ClientHandler *clientWithWhiteFigures;
    ChessMatch chessMatch;

private:

};

#endif // CHESSTABLE_H
