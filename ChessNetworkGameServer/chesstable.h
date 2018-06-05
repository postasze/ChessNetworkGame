#ifndef CHESSTABLE_H
#define CHESSTABLE_H

#include <vector>

class ClientHandler;
class ChessMatch;

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
