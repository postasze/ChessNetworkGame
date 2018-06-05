#include "chessmatch.h"

ChessMatch::ChessMatch()
{
    createFigures();
    createBoard();

    currentPlayerColor = PlayerColor::White;
}

void ChessMatch::createFigures()
{
    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; ++i)
        whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Pawn, std::pair<int, int>(i * SQUARE_SIZE, 6 * SQUARE_SIZE), whitePawnPixmap));

    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; ++i)
        blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Pawn, std::pair<int, int>(i * SQUARE_SIZE, 1 * SQUARE_SIZE), blackPawnPixmap));

    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::LeftRook, std::pair<int, int>(0 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteRookPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::RightRook, std::pair<int, int>(7 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteRookPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::LeftRook, std::pair<int, int>(0 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackRookPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::RightRook, std::pair<int, int>(7 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackRookPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Knight, std::pair<int, int>(1 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteKnightPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Knight, std::pair<int, int>(6 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteKnightPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Knight, std::pair<int, int>(1 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackKnightPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Knight, std::pair<int, int>(6 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackKnightPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Bishop, std::pair<int, int>(2 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteBishopPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Bishop, std::pair<int, int>(5 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteBishopPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Bishop, std::pair<int, int>(2 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackBishopPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Bishop, std::pair<int, int>(5 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackBishopPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Queen, std::pair<int, int>(3 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteQueenPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::King, std::pair<int, int>(4 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteKingPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Queen, std::pair<int, int>(3 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackQueenPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::King, std::pair<int, int>(4 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackKingPixmap));
}

void ChessMatch::createBoard()
{
    std::pair<int, int> boardPoint;

    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; ++i)
        for(unsigned int j = 0; j < NUMBER_OF_SQUARES; ++j)
            board[i][j] = nullptr;

    foreach (Figure *figure, blackFigures)
    {
        boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos());
        board[boardPoint.x()][boardPoint.y()] = figure;
    }

    foreach (Figure *figure, whiteFigures)
    {
        boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos());
        board[boardPoint.x()][boardPoint.y()] = figure;
    }
}

void ChessMatch::pawnPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    std::pair<int, int> boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board

    switch(figure->figureColor)
    {
    case PlayerColor::Black:
        if(boardPoint.y() == 0) // end of board for pawn
            return; // returning empty possible moves

        if(board[boardPoint.x()][boardPoint.y()-1] == nullptr)
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x(), boardPoint.y()-1));

        if(boardPoint.y() == 6 && board[boardPoint.x()][5] == nullptr && board[boardPoint.x()][4] == nullptr)
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x(), 4));

        if(boardPoint.x() > 0 && boardPoint.y() > 0)
            if(board[boardPoint.x()-1][boardPoint.y()-1] != nullptr)
                if(board[boardPoint.x()-1][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-1, boardPoint.y()-1));

        if(boardPoint.x() < 7 && boardPoint.y() > 0)
            if(board[boardPoint.x()+1][boardPoint.y()-1] != nullptr)
                if(board[boardPoint.x()+1][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+1, boardPoint.y()-1));
        break;
    case PlayerColor::White:
        if(boardPoint.y() == 7) // end of board for pawn
            return; // returning empty possible moves

        if(board[boardPoint.x()][boardPoint.y()+1] == nullptr)
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x(), boardPoint.y()+1));

        if(boardPoint.y() == 1 && board[boardPoint.x()][2] == nullptr && board[boardPoint.x()][3] == nullptr)
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x(), 3));

        if(boardPoint.x() > 0 && boardPoint.y() < 7)
            if(board[boardPoint.x()-1][boardPoint.y()+1] != nullptr)
                if(board[boardPoint.x()-1][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-1, boardPoint.y()+1));

        if(boardPoint.x() < 7 && boardPoint.y() < 7)
            if(board[boardPoint.x()+1][boardPoint.y()+1] != nullptr)
                if(board[boardPoint.x()+1][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+1, boardPoint.y()+1));
        break;
    }
}

void ChessMatch::knightPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    std::pair<int, int> boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board

    if(boardPoint.x() < 7 && boardPoint.y() < 6)
        if (board[boardPoint.x()+1][boardPoint.y()+2] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()+2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+1, boardPoint.y()+2));

    if(boardPoint.x() < 6 && boardPoint.y() < 7)
        if (board[boardPoint.x()+2][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()+2][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+2, boardPoint.y()+1));

    if(boardPoint.x() < 6 && boardPoint.y() > 0)
        if (board[boardPoint.x()+2][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()+2][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+2, boardPoint.y()-1));

    if(boardPoint.x() < 7 && boardPoint.y() > 1)
        if (board[boardPoint.x()+1][boardPoint.y()-2] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()-2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+1, boardPoint.y()-2));

    if(boardPoint.x() > 0 && boardPoint.y() > 1)
        if (board[boardPoint.x()-1][boardPoint.y()-2] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()-2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-1, boardPoint.y()-2));

    if(boardPoint.x() > 1 && boardPoint.y() > 0)
        if (board[boardPoint.x()-2][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()-2][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-2, boardPoint.y()-1));

    if(boardPoint.x() > 1 && boardPoint.y() < 7)
        if (board[boardPoint.x()-2][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()-2][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-2, boardPoint.y()+1));

    if(boardPoint.x() > 0 && boardPoint.y() < 6)
        if (board[boardPoint.x()-1][boardPoint.y()+2] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()+2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-1, boardPoint.y()+2));
}

void ChessMatch::kingPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    std::pair<int, int> boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board

    if(isShortCastlingPossible())
        possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+3,boardPoint.y()));

    if(isLongCastlingPossible())
        possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-4, boardPoint.y()));

    if(boardPoint.y() < 7)
        if (board[boardPoint.x()][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x(), boardPoint.y()+1));

    if(boardPoint.x() < 7 && boardPoint.y() < 7)
        if (board[boardPoint.x()+1][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+1, boardPoint.y()+1));

    if(boardPoint.x() < 7)
        if (board[boardPoint.x()+1][boardPoint.y()] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+1, boardPoint.y()));

    if(boardPoint.x() < 7 && boardPoint.y() > 0)
        if (board[boardPoint.x()+1][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()+1, boardPoint.y()-1));

    if(boardPoint.y() > 0)
        if (board[boardPoint.x()][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x(), boardPoint.y()-1));

    if(boardPoint.x() > 0 && boardPoint.y() > 0)
        if (board[boardPoint.x()-1][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-1, boardPoint.y()-1));

    if(boardPoint.x() > 0)
        if (board[boardPoint.x()-1][boardPoint.y()] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-1, boardPoint.y()));

    if(boardPoint.x() > 0 && boardPoint.y() < 7)
        if (board[boardPoint.x()-1][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.x()-1, boardPoint.y()+1));

    if(figure->figureColor == currentPlayerColor)
        eraseForbiddenKingMoves(possibleMoves);
}

// function which tries to add consistently all possible moves in direction chosen by h - horizontal factor and v - vertical factor, v and h can be only 3 values (-1, 0, 1)
void ChessMatch::addAllPossibleMovesInDirection(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves, int h, int v)
{
    std::pair<int, int> boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board
    int x, y, i = 1;

    while(true)
    {
        x = boardPoint.x() + h*i;
        y = boardPoint.y() + v*i;

        if(0 <= x && x <= 7 && 0 <= y && y <= 7)
        {
            if (board[x][y] == nullptr)
                possibleMoves.push_back(std::pair<int, int>(x, y));

            else if (board[x][y]->figureColor == getOpponentColor(currentPlayerColor))
            {
                possibleMoves.push_back(std::pair<int, int>(x, y));
                break;
            }
            else if (board[x][y]->figureColor == currentPlayerColor)
                break;
        }
        else
            break;
        ++i;
    }
}

void ChessMatch::bishopPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, 1); // up right
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, -1); // down right
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, -1); // down left
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, 1); // up left
}

void ChessMatch::rookPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    addAllPossibleMovesInDirection(figure, possibleMoves, 0, 1); // up
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, 0); // right
    addAllPossibleMovesInDirection(figure, possibleMoves, 0, -1); // down
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, 0); // left
}

void ChessMatch::queenPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    addAllPossibleMovesInDirection(figure, possibleMoves, 0, 1); // up
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, 1); // up right
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, 0); // right
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, -1); // down right
    addAllPossibleMovesInDirection(figure, possibleMoves, 0, -1); // down
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, -1); // down left
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, 0); // left
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, 1); // up left
}

void ChessMatch::findPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    possibleMoves.clear();

    switch(figure->figureType)
    {
    case FigureType::Pawn:
        pawnPossibleMoves(figure, possibleMoves);
        break;
    case FigureType::Knight:
        knightPossibleMoves(figure, possibleMoves);
        break;
    case FigureType::Bishop:
        bishopPossibleMoves(figure, possibleMoves);
        break;
    case FigureType::LeftRook:
        rookPossibleMoves(figure, possibleMoves);
        break;
    case FigureType::RightRook:
        rookPossibleMoves(figure, possibleMoves);
        break;
    case FigureType::Queen:
        queenPossibleMoves(figure, possibleMoves);
        break;
    case FigureType::King:
        kingPossibleMoves(figure, possibleMoves);
        break;
    }
}


void ChessMatch::promotePawn(Figure* promotedOne)
{
    promotedOne->figureType = FigureType::Queen;
}

bool ChessMatch::isShortCastlingPossible()
{
    if (currentPlayerColor == PlayerColor::White)
    {
        if (whiteFlags.isShortCastlingPossible() && board[5][0] == nullptr && board[6][0] == nullptr)
            return true;
      //  else
         //   return false;
    }

    else if (currentPlayerColor == PlayerColor::Black)
    {
        if (blackFlags.isShortCastlingPossible() && board[5][7] == nullptr && board[6][7] == nullptr)
            return true;
   //     else
        //    return false;
    }

    return false;
}

bool ChessMatch::isLongCastlingPossible()
{
    if (currentPlayerColor == PlayerColor::White)
    {
        if (whiteFlags.isLongCastlingPossible() && board[1][0] == nullptr && board[2][0] == nullptr && board[3][0] == nullptr)
            return true;
    }

    else if (currentPlayerColor == PlayerColor::Black)
    {
        if (blackFlags.isLongCastlingPossible() && board[1][7] == nullptr && board[2][7] == nullptr && board[3][7] == nullptr)
            return true;

    }
    return false;
}

void ChessMatch::eraseForbiddenKingMoves(std::vector<std::pair<int, int>>& possibleMoves)
{
    std::vector<std::pair<int, int>> forbiddenMoves;
    std::vector<std::pair<int, int>>::iterator iter;

    if (currentPlayerColor == PlayerColor::White)
    {
        for(unsigned int i = 0; i < blackFigures.size(); i++)
        {
            findPossibleMoves(blackFigures[i], forbiddenMoves);
            for(unsigned int j = 0; j < possibleMoves.size(); j++)
                if((iter = std::find(forbiddenMoves.begin(), forbiddenMoves.end(), possibleMoves[j])) != forbiddenMoves.end())
                    possibleMoves.erase(iter);
        }
    }
    else
    {
        for(unsigned int i = 0; i < whiteFigures.size(); i++)
        {
            findPossibleMoves(whiteFigures[i], forbiddenMoves);
            for(unsigned int j = 0; j < possibleMoves.size(); j++)
                if((iter = std::find(forbiddenMoves.begin(), forbiddenMoves.end(), possibleMoves[j])) != forbiddenMoves.end())
                    possibleMoves.erase(iter);
        }
    }
}

//bool ChessMatch::isKingChecked()
