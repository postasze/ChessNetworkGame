#ifndef CHESSMATCH_H
#define CHESSMATCH_H

#include <vector>
#include "constants.h"
#include "figure.h"

class ChessMatch
{
public:
    ChessMatch();

    std::vector<std::pair<int, int>> getPossibleMovesForFigureOnPosition(int x, int y);
    std::pair<int, int> makePlayerMove(std::pair<int, int> destinationPoint);
    bool blackPlayerReady, whitePlayerReady;

private:
    void createFigures();
    void createBlackFigures();
    void createWhiteFigures();
    void createBoard();

    void findPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves);
    void addAllPossibleMovesInDirection(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves, int h, int v);
    void pawnPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves);
    void knightPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves);
    void bishopPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves);
    void rookPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves);
    void queenPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves);
    void kingPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves);
    void eraseForbiddenKingMoves(std::vector<std::pair<int, int>>& possibleMoves);
    void promotePawn(Figure* promotedOne);
    PlayerColor getOpponentColor(PlayerColor playerColor);
    void removeFigureOnSquare(std::pair<int, int> boardPoint);

    Figure* board[NUMBER_OF_SQUARES][NUMBER_OF_SQUARES];
    std::vector<Figure*> blackFigures, whiteFigures;
    PlayerColor currentPlayerColor;
    std::vector<std::pair<int, int>> possibleMoves;
    Figure *selectedFigure;

    struct CastlingFlags
    {
        CastlingFlags(): hasKingBeenMoved(false),hasLeftRookBeenMoved(false), hasRightRookBeenMoved(false) {}

        bool hasKingBeenMoved;
        bool hasLeftRookBeenMoved;
        bool hasRightRookBeenMoved;

        bool isShortCastlingPossible()
        {
            return (!hasKingBeenMoved && !hasRightRookBeenMoved);
        }

        bool isLongCastlingPossible()
        {
            return (!hasKingBeenMoved && !hasLeftRookBeenMoved);
        }

    };

    CastlingFlags whiteFlags;
    CastlingFlags blackFlags;

    bool isShortCastlingPossible();
    bool isLongCastlingPossible();
};

#endif // CHESSMATCH_H
