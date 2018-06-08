#include "chessmatch.h"
#include <algorithm>

ChessMatch::ChessMatch()
{
    createFigures();
    createBoard();

    currentPlayerColor = PlayerColor::White;
    selectedFigure = nullptr;
    blackPlayerReady = false;
    whitePlayerReady = false;
    isBlackKingChecked = false;
    isWhiteKingChecked = false;
}

void ChessMatch::createFigures()
{
    createBlackFigures();
    createWhiteFigures();
}

void ChessMatch::createBlackFigures()
{
    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; ++i)
        blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Pawn, i, 6));

    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::LeftRook, 0, 7));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::RightRook, 7, 7));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Knight, 1, 7));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Knight, 6, 7));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Bishop, 2, 7));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Bishop, 5, 7));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Queen, 3, 7));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::King, 4, 7));
}

void ChessMatch::createWhiteFigures()
{
    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; ++i)
        whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Pawn, i, 1));

    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::LeftRook, 0, 0));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::RightRook, 7, 0));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Knight, 1, 0));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Knight, 6, 0));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Bishop, 2, 0));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Bishop, 5, 0));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Queen, 3, 0));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::King, 4, 0));
}

void ChessMatch::createBoard()
{
    std::pair<int, int> boardPoint;

    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; ++i)
        for(unsigned int j = 0; j < NUMBER_OF_SQUARES; ++j)
            board[i][j] = nullptr;

    for(unsigned int i = 0; i < blackFigures.size(); i++)
    {
        boardPoint = std::make_pair(blackFigures[i]->x, blackFigures[i]->y);
        board[boardPoint.first][boardPoint.second] = blackFigures[i];
    }

    for(unsigned int i = 0; i < whiteFigures.size(); i++)
    {
        boardPoint = std::make_pair(whiteFigures[i]->x, whiteFigures[i]->y);
        board[boardPoint.first][boardPoint.second] = whiteFigures[i];
    }
}

void ChessMatch::pawnPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves, bool toEliminate)
{
    std::pair<int, int> boardPoint = std::make_pair(figure->x, figure->y); // position of figure on the board

    switch(figure->figureColor)
    {
    if(toEliminate == false)
    {
        case PlayerColor::Black:
        if(boardPoint.second == 0) // end of board for pawn
            return; // returning empty possible moves

        if(board[boardPoint.first][boardPoint.second-1] == nullptr)
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first, boardPoint.second-1));

        if(boardPoint.second == 6 && board[boardPoint.first][5] == nullptr && board[boardPoint.first][4] == nullptr)
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first, 4));

        if(boardPoint.first > 0 && boardPoint.second > 0)
            if(board[boardPoint.first-1][boardPoint.second-1] != nullptr)
                if(board[boardPoint.first-1][boardPoint.second-1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second-1));

        if(boardPoint.first < 7 && boardPoint.second > 0)
            if(board[boardPoint.first+1][boardPoint.second-1] != nullptr)
                if(board[boardPoint.first+1][boardPoint.second-1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second-1));
    }
    else
    {
        if(boardPoint.first > 0 && boardPoint.second > 0)
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second-1));
        if(boardPoint.first < 7 && boardPoint.second > 0)
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second-1));

    }
        break;
    case PlayerColor::White:
        if(toEliminate == false)
        {
            if(boardPoint.second == 7) // end of board for pawn
                return; // returning empty possible moves

            if(board[boardPoint.first][boardPoint.second+1] == nullptr)
                possibleMoves.push_back(std::pair<int, int>(boardPoint.first, boardPoint.second+1));

            if(boardPoint.second == 1 && board[boardPoint.first][2] == nullptr && board[boardPoint.first][3] == nullptr)
                possibleMoves.push_back(std::pair<int, int>(boardPoint.first, 3));

            if(boardPoint.first > 0 && boardPoint.second < 7)
                if(board[boardPoint.first-1][boardPoint.second+1] != nullptr)
                    if(board[boardPoint.first-1][boardPoint.second+1]->figureColor == getOpponentColor(currentPlayerColor))
                        possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second+1));

            if(boardPoint.first < 7 && boardPoint.second < 7)
                if(board[boardPoint.first+1][boardPoint.second+1] != nullptr)
                    if(board[boardPoint.first+1][boardPoint.second+1]->figureColor == getOpponentColor(currentPlayerColor))
                        possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second+1));
        }
        else
        {
         if(boardPoint.first > 0 && boardPoint.second < 7)
             possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second+1));
         if(boardPoint.first < 7 && boardPoint.second < 7)
             possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second+1));
        }
        break;
    }
}

void ChessMatch::knightPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    std::pair<int, int> boardPoint = std::make_pair(figure->x, figure->y); // position of figure on the board

    if(boardPoint.first < 7 && boardPoint.second < 6)
        if (board[boardPoint.first+1][boardPoint.second+2] == nullptr ||
            board[boardPoint.first+1][boardPoint.second+2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second+2));

    if(boardPoint.first < 6 && boardPoint.second < 7)
        if (board[boardPoint.first+2][boardPoint.second+1] == nullptr ||
            board[boardPoint.first+2][boardPoint.second+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first+2, boardPoint.second+1));

    if(boardPoint.first < 6 && boardPoint.second > 0)
        if (board[boardPoint.first+2][boardPoint.second-1] == nullptr ||
            board[boardPoint.first+2][boardPoint.second-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first+2, boardPoint.second-1));

    if(boardPoint.first < 7 && boardPoint.second > 1)
        if (board[boardPoint.first+1][boardPoint.second-2] == nullptr ||
            board[boardPoint.first+1][boardPoint.second-2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second-2));

    if(boardPoint.first > 0 && boardPoint.second > 1)
        if (board[boardPoint.first-1][boardPoint.second-2] == nullptr ||
            board[boardPoint.first-1][boardPoint.second-2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second-2));

    if(boardPoint.first > 1 && boardPoint.second > 0)
        if (board[boardPoint.first-2][boardPoint.second-1] == nullptr ||
            board[boardPoint.first-2][boardPoint.second-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first-2, boardPoint.second-1));

    if(boardPoint.first > 1 && boardPoint.second < 7)
        if (board[boardPoint.first-2][boardPoint.second+1] == nullptr ||
            board[boardPoint.first-2][boardPoint.second+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first-2, boardPoint.second+1));

    if(boardPoint.first > 0 && boardPoint.second < 6)
        if (board[boardPoint.first-1][boardPoint.second+2] == nullptr ||
            board[boardPoint.first-1][boardPoint.second+2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second+2));
}

void ChessMatch::kingPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves)
{
    std::pair<int, int> boardPoint = std::make_pair(figure->x, figure->y); // position of figure on the board

    if(isShortCastlingPossible())
        possibleMoves.push_back(std::pair<int, int>(boardPoint.first+3,boardPoint.second));

    if(isLongCastlingPossible())
        possibleMoves.push_back(std::pair<int, int>(boardPoint.first-4, boardPoint.second));

    if(boardPoint.second < 7)
        if (board[boardPoint.first][boardPoint.second+1] == nullptr ||
            board[boardPoint.first][boardPoint.second+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first, boardPoint.second+1));

    if(boardPoint.first < 7 && boardPoint.second < 7)
        if (board[boardPoint.first+1][boardPoint.second+1] == nullptr ||
            board[boardPoint.first+1][boardPoint.second+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second+1));

    if(boardPoint.first < 7)
        if (board[boardPoint.first+1][boardPoint.second] == nullptr ||
            board[boardPoint.first+1][boardPoint.second]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second));

    if(boardPoint.first < 7 && boardPoint.second > 0)
        if (board[boardPoint.first+1][boardPoint.second-1] == nullptr ||
            board[boardPoint.first+1][boardPoint.second-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first+1, boardPoint.second-1));

    if(boardPoint.second > 0)
        if (board[boardPoint.first][boardPoint.second-1] == nullptr ||
            board[boardPoint.first][boardPoint.second-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first, boardPoint.second-1));

    if(boardPoint.first > 0 && boardPoint.second > 0)
        if (board[boardPoint.first-1][boardPoint.second-1] == nullptr ||
            board[boardPoint.first-1][boardPoint.second-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second-1));

    if(boardPoint.first > 0)
        if (board[boardPoint.first-1][boardPoint.second] == nullptr ||
            board[boardPoint.first-1][boardPoint.second]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second));

    if(boardPoint.first > 0 && boardPoint.second < 7)
        if (board[boardPoint.first-1][boardPoint.second+1] == nullptr ||
            board[boardPoint.first-1][boardPoint.second+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(std::pair<int, int>(boardPoint.first-1, boardPoint.second+1));

    if(figure->figureColor == currentPlayerColor)
        eraseForbiddenKingMoves(possibleMoves);
}

// function which tries to add consistently all possible moves in direction chosen by h - horizontal factor and v - vertical factor, v and h can be only 3 values (-1, 0, 1)
void ChessMatch::addAllPossibleMovesInDirection(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves, int h, int v)
{
    std::pair<int, int> boardPoint = std::make_pair(figure->x, figure->y); // position of figure on the board
    int x, y, i = 1;

    while(true)
    {
        x = boardPoint.first + h*i;
        y = boardPoint.second + v*i;

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

void ChessMatch::findPossibleMoves(Figure *figure, std::vector<std::pair<int, int>>& possibleMoves, bool toEliminate)
{
    possibleMoves.clear();

    switch(figure->figureType)
    {
    case FigureType::Pawn:
        pawnPossibleMoves(figure, possibleMoves, toEliminate);
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
    }

    else if (currentPlayerColor == PlayerColor::Black)
    {
        if (blackFlags.isShortCastlingPossible() && board[5][7] == nullptr && board[6][7] == nullptr)
            return true;

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
        {   if(blackFigures[i]->figureType == FigureType::Pawn)
                findPossibleMoves(blackFigures[i], forbiddenMoves,true);
            else
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
            if(whiteFigures[i]->figureType == FigureType::Pawn)
                findPossibleMoves(whiteFigures[i], forbiddenMoves,true);
            else
                findPossibleMoves(whiteFigures[i], forbiddenMoves);
            for(unsigned int j = 0; j < possibleMoves.size(); j++)
                if((iter = std::find(forbiddenMoves.begin(), forbiddenMoves.end(), possibleMoves[j])) != forbiddenMoves.end())
                    possibleMoves.erase(iter);
        }
    }
}

PlayerColor ChessMatch::getOpponentColor(PlayerColor playerColor)
{
    return (PlayerColor) (1 - playerColor);
}

std::vector<std::pair<int, int>> ChessMatch::getPossibleMovesForFigureOnPosition(int x, int y)
{
    std::vector<std::pair<int, int>> possibleMoves;
    selectedFigure = board[x][y];

    findPossibleMoves(selectedFigure, possibleMoves);

    return possibleMoves;
}

std::pair<int, int> ChessMatch::makePlayerMove(std::pair<int, int> destinationPoint)
{
    std::pair<int, int> startPoint = std::make_pair(selectedFigure->x, selectedFigure->y);

    if (board[destinationPoint.first][destinationPoint.second] != nullptr && (board[destinationPoint.first][destinationPoint.second])->figureType == FigureType::RightRook && (board[destinationPoint.first][destinationPoint.second])->figureColor == currentPlayerColor) // short castling
    {
        std::pair<int, int> newRookPoint = destinationPoint;
        newRookPoint.first -= 2;
        std::pair<int, int> newKingPoint = destinationPoint;
        newKingPoint.first -= 1;

        board[newKingPoint.first][newKingPoint.second] = selectedFigure;
        board[newRookPoint.first][newRookPoint.second] = board[destinationPoint.first][destinationPoint.second];
        board[newRookPoint.first][newRookPoint.second]->x = newRookPoint.first;
        board[newRookPoint.first][newRookPoint.second]->y = newRookPoint.second;
        selectedFigure->x = newKingPoint.first;
        selectedFigure->y = newKingPoint.second;
        board[selectedFigure->x][selectedFigure->y] = nullptr;
        board[destinationPoint.first][destinationPoint.second] = nullptr;
    }
    else if (board[destinationPoint.first][destinationPoint.second] != nullptr && board[destinationPoint.first][destinationPoint.second]->figureType == FigureType::LeftRook && (board[destinationPoint.first][destinationPoint.second])->figureColor == currentPlayerColor) //long castling
    {
        std::pair<int, int> newRookPoint = destinationPoint;
        newRookPoint.first += 3;
        std::pair<int, int> newKingPoint = destinationPoint;
        newKingPoint.first += 2;

        board[newKingPoint.first][newKingPoint.second] = selectedFigure;
        board[newRookPoint.first][newRookPoint.second] = board[destinationPoint.first][destinationPoint.second];
        board[newRookPoint.first][newRookPoint.second]->x = newRookPoint.first;
        board[newRookPoint.first][newRookPoint.second]->y = newRookPoint.second;
        selectedFigure->x = newKingPoint.first;
        selectedFigure->y = newKingPoint.second;
        board[selectedFigure->x][selectedFigure->y] = nullptr;
        board[destinationPoint.first][destinationPoint.second] = nullptr;
    }
    else
    {
        if(board[destinationPoint.first][destinationPoint.second] != nullptr)
            removeFigureOnSquare(destinationPoint); // removal of opponent figure on this square
        board[selectedFigure->x][selectedFigure->y] = nullptr;
        board[destinationPoint.first][destinationPoint.second] = selectedFigure;
        selectedFigure->x = destinationPoint.first;
        selectedFigure->y = destinationPoint.second;
    }

    //promote pawn, if reached end of the board
    if (selectedFigure->figureType == FigureType::Pawn && (destinationPoint.second == 7 || destinationPoint.second == 0))
        promotePawn(selectedFigure);

    // set flags, so that castling won't be possible anymore
    if(currentPlayerColor == PlayerColor::White)
    {
        switch (selectedFigure->figureType) {
        case FigureType::King:
            whiteFlags.hasKingBeenMoved = true;
            break;
        case FigureType::LeftRook:
            whiteFlags.hasLeftRookBeenMoved = true;
            break;
        case FigureType::RightRook:
            whiteFlags.hasRightRookBeenMoved = true;
            break;
        default:
            break;
        }
    }
    else if(currentPlayerColor == PlayerColor::Black)
    {
        switch (selectedFigure->figureType) {

        case FigureType::King:
            blackFlags.hasKingBeenMoved = true;
            break;
        case FigureType::LeftRook:
            blackFlags.hasLeftRookBeenMoved = true;
            break;
        case FigureType::RightRook:
            blackFlags.hasRightRookBeenMoved = true;
            break;
        default:
            break;
        }
    }
   setKingChecked();
    currentPlayerColor = getOpponentColor(currentPlayerColor);

    return startPoint;
}

void ChessMatch::removeFigureOnSquare(std::pair<int, int> boardPoint)
{
    switch(getOpponentColor(currentPlayerColor))
    {
    case PlayerColor::Black:
        blackFigures.erase(std::find(blackFigures.begin(), blackFigures.end(), board[boardPoint.first][boardPoint.second]));
        break;
    case PlayerColor::White:
        whiteFigures.erase(std::find(whiteFigures.begin(), whiteFigures.end(), board[boardPoint.first][boardPoint.second]));
        break;
    }
    delete board[boardPoint.first][boardPoint.second];
}
void ChessMatch::setKingChecked()
{
    std::vector<std::pair<int, int>> forbiddenMoves;
    //std::vector<std::pair<int, int>>::iterator iter;
     std::pair<int, int> kingPosition;

        if (currentPlayerColor == PlayerColor::White || isBlackKingChecked )
        {
            for(unsigned int i = 0; i < blackFigures.size(); ++i)
               if(blackFigures[i]->figureType == FigureType::King)
                    kingPosition = std::make_pair(blackFigures[i]->x, blackFigures[i]->y);

            for (unsigned int j = 0; j< whiteFigures.size(); ++j)
            {
                if(whiteFigures[j]->figureType == FigureType::Pawn)
                    findPossibleMoves(whiteFigures[j], forbiddenMoves,true);
                else
                    findPossibleMoves(whiteFigures[j], forbiddenMoves);
               if(std::find(forbiddenMoves.begin(), forbiddenMoves.end(), kingPosition) != forbiddenMoves.end())
               {
                   isBlackKingChecked = true;
                   return;
               }
            }
            isBlackKingChecked = false;

         }
        else if (currentPlayerColor == PlayerColor::Black || isWhiteKingChecked)
        {
                 for(unsigned int i = 0; i < whiteFigures.size(); ++i)
                    if(whiteFigures[i]->figureType == FigureType::King)
                        kingPosition = std::make_pair(whiteFigures[i]->x, whiteFigures[i]->y);

                    for (unsigned int j = 0; j < blackFigures.size(); ++j)
                    {
                        if(blackFigures[j]->figureType == FigureType::Pawn)
                            findPossibleMoves(blackFigures[j], forbiddenMoves, true);
                        else
                             findPossibleMoves(blackFigures[j], forbiddenMoves);

                        if(std::find(forbiddenMoves.begin(), forbiddenMoves.end(), kingPosition) != forbiddenMoves.end())
                        {
                            isWhiteKingChecked = true;
                            return;
                        }

                    }
                    isWhiteKingChecked =  false;

          }


}



