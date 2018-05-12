#include "chessgamewidget.h"
#include <iostream>

ChessGameWidget::ChessGameWidget(QWidget *parent) : QWidget(parent)
{
    chessView.setParent(this);
    chessScene.setParent(&chessView);
    chessView.setScene(&chessScene);
    chessView.setFixedSize(BOARD_WIDTH, BOARD_HEIGHT);
    chessScene.setSceneRect(0, 0, BOARD_WIDTH, BOARD_HEIGHT);
    chessView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chessView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chessView.setBackgroundBrush(QBrush(DARK_FIELD_COLOR));

    chessBoardPixmapItem.setPixmap(QPixmap::fromImage(QImage(":/images/chess_board/chess_board.png")));
    chessScene.addItem(&chessBoardPixmapItem);

    loadFigureImages();
    createFigures();
    createBoard();
    addFigureImagesToScene();

    draggedFigure = nullptr;
    currentPlayerColor = PlayerColor::White;
}

ChessGameWidget::~ChessGameWidget()
{

}

void ChessGameWidget::loadFigureImages()
{
    blackPawnPixmap.load(":/images/figures/black_pawn.png");
    blackKnightPixmap.load(":/images/figures/black_knight.png");
    blackBishopPixmap.load(":/images/figures/black_bishop.png");
    blackRookPixmap.load(":/images/figures/black_rook.png");
    blackQueenPixmap.load(":/images/figures/black_queen.png");
    blackKingPixmap.load(":/images/figures/black_king.png");
    whitePawnPixmap.load(":/images/figures/white_pawn.png");
    whiteKnightPixmap.load(":/images/figures/white_knight.png");
    whiteBishopPixmap.load(":/images/figures/white_bishop.png");
    whiteRookPixmap.load(":/images/figures/white_rook.png");
    whiteQueenPixmap.load(":/images/figures/white_queen.png");
    whiteKingPixmap.load(":/images/figures/white_king.png");
}

void ChessGameWidget::createFigures()
{
    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; i++)
        whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Pawn, QPointF(i * SQUARE_SIZE, 6 * SQUARE_SIZE), whitePawnPixmap));

    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; i++)
        blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Pawn, QPointF(i * SQUARE_SIZE, 1 * SQUARE_SIZE), blackPawnPixmap));

    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Rook, QPointF(0 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteRookPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Rook, QPointF(7 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteRookPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Rook, QPointF(0 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackRookPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Rook, QPointF(7 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackRookPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Knight, QPointF(1 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteKnightPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Knight, QPointF(6 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteKnightPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Knight, QPointF(1 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackKnightPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Knight, QPointF(6 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackKnightPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Bishop, QPointF(2 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteBishopPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Bishop, QPointF(5 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteBishopPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Bishop, QPointF(2 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackBishopPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Bishop, QPointF(5 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackBishopPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Queen, QPointF(3 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteQueenPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::King, QPointF(4 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteKingPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Queen, QPointF(3 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackQueenPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::King, QPointF(4 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackKingPixmap));
}

void ChessGameWidget::createBoard()
{
    QPoint boardPoint;

    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; i++)
        for(unsigned int j = 0; j < NUMBER_OF_SQUARES; j++)
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

void ChessGameWidget::addFigureImagesToScene()
{
    foreach (Figure *figure, blackFigures)
    {
        figure->setZValue(1);
        chessScene.addItem(figure);
    }

    foreach (Figure *figure, whiteFigures)
    {
        figure->setZValue(1);
        chessScene.addItem(figure);
    }
}

void ChessGameWidget::mousePressEvent(QMouseEvent *event)
{
    std::cout << "mousePressEvent" << std::endl;

    draggedFigure = dynamic_cast<Figure*>(chessScene.itemAt(event->pos(), QTransform()));

    if(draggedFigure != nullptr && draggedFigure->figureColor == currentPlayerColor)
    {
        findPossibleMoves(draggedFigure, possibleMoves);
        createPossibleMoveSquares(possibleMoves);
        draggingStartPosition = draggedFigure->pos();
    }
    else
        draggedFigure = nullptr;
}

void ChessGameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "mouseReleaseEvent" << std::endl;

    if(draggedFigure != nullptr)
    {
        QPoint boardPoint = pixelCoordinatesToBoardCoordinates(event->pos());

        if ((std::find(possibleMoves.begin(), possibleMoves.end(), boardPoint) == possibleMoves.end()) ||
            (board[boardPoint.x()][boardPoint.y()] != nullptr && board[boardPoint.x()][boardPoint.y()]->figureColor == currentPlayerColor))
            draggedFigure->setPos(draggingStartPosition); // situation when move is invalid
        else // situation when move is valid
        {
            QPointF scenePosition = boardCoordinatesToPixelCoordinates(boardPoint);
            QPoint draggingStartPoint = pixelCoordinatesToBoardCoordinates(draggingStartPosition);

            board[draggingStartPoint.x()][draggingStartPoint.y()] = nullptr;
            delete board[boardPoint.x()][boardPoint.y()]; // removal of opponent figure if there is any on this square
            board[boardPoint.x()][boardPoint.y()] = draggedFigure;
            draggedFigure->setPos(scenePosition);

            currentPlayerColor = getOpponentColor(currentPlayerColor);
        }

        deletePossibleMoveSquares();
        draggedFigure = nullptr;
    }
}

void ChessGameWidget::mouseMoveEvent(QMouseEvent *event)
{
    std::cout << "mouseMoveEvent" << std::endl;

    if(draggedFigure != nullptr)
        draggedFigure->setPos(event->pos() -= QPoint(SQUARE_SIZE / 2, SQUARE_SIZE / 2));
}

void ChessGameWidget::pawnPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves)
{
    QPoint boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board

    switch(figure->figureColor)
    {
    case PlayerColor::Black:
        if(boardPoint.y() == 0) // end of board for pawn
            return; // returning empty possible moves

        if(board[boardPoint.x()][boardPoint.y()-1] == nullptr)
            possibleMoves.push_back(QPoint(boardPoint.x(), boardPoint.y()-1));

        if(boardPoint.y() == 6 && board[boardPoint.x()][5] == nullptr && board[boardPoint.x()][4] == nullptr)
            possibleMoves.push_back(QPoint(boardPoint.x(), 4));

        if(boardPoint.x() > 0 && boardPoint.y() > 0)
            if(board[boardPoint.x()-1][boardPoint.y()-1] != nullptr)
                if(board[boardPoint.x()-1][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(QPoint(boardPoint.x()-1, boardPoint.y()-1));

        if(boardPoint.x() < 7 && boardPoint.y() > 0)
            if(board[boardPoint.x()+1][boardPoint.y()-1] != nullptr)
                if(board[boardPoint.x()+1][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(QPoint(boardPoint.x()+1, boardPoint.y()-1));
        break;
    case PlayerColor::White:
        if(boardPoint.y() == 7) // end of board for pawn
            return; // returning empty possible moves

        if(board[boardPoint.x()][boardPoint.y()+1] == nullptr)
            possibleMoves.push_back(QPoint(boardPoint.x(), boardPoint.y()+1));

        if(boardPoint.y() == 1 && board[boardPoint.x()][2] == nullptr && board[boardPoint.x()][3] == nullptr)
            possibleMoves.push_back(QPoint(boardPoint.x(), 3));

        if(boardPoint.x() > 0 && boardPoint.y() < 7)
            if(board[boardPoint.x()-1][boardPoint.y()+1] != nullptr)
                if(board[boardPoint.x()-1][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(QPoint(boardPoint.x()-1, boardPoint.y()+1));

        if(boardPoint.x() < 7 && boardPoint.y() < 7)
            if(board[boardPoint.x()+1][boardPoint.y()+1] != nullptr)
                if(board[boardPoint.x()+1][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
                    possibleMoves.push_back(QPoint(boardPoint.x()+1, boardPoint.y()+1));
        break;
    }
}

void ChessGameWidget::knightPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves)
{
    QPoint boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board

    if(boardPoint.x() < 7 && boardPoint.y() < 6)
        if (board[boardPoint.x()+1][boardPoint.y()+2] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()+2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()+1, boardPoint.y()+2));

    if(boardPoint.x() < 6 && boardPoint.y() < 7)
        if (board[boardPoint.x()+2][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()+2][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()+2, boardPoint.y()+1));

    if(boardPoint.x() < 6 && boardPoint.y() > 0)
        if (board[boardPoint.x()+2][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()+2][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()+2, boardPoint.y()-1));

    if(boardPoint.x() < 7 && boardPoint.y() > 1)
        if (board[boardPoint.x()+1][boardPoint.y()-2] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()-2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()+1, boardPoint.y()-2));

    if(boardPoint.x() > 0 && boardPoint.y() > 1)
        if (board[boardPoint.x()-1][boardPoint.y()-2] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()-2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()-1, boardPoint.y()-2));

    if(boardPoint.x() > 1 && boardPoint.y() > 0)
        if (board[boardPoint.x()-2][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()-2][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()-2, boardPoint.y()-1));

    if(boardPoint.x() > 1 && boardPoint.y() < 7)
        if (board[boardPoint.x()-2][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()-2][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()-2, boardPoint.y()+1));

    if(boardPoint.x() > 0 && boardPoint.y() < 6)
        if (board[boardPoint.x()-1][boardPoint.y()+2] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()+2]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()-1, boardPoint.y()+2));
}

void ChessGameWidget::kingPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves)
{
    QPoint boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board

    if(boardPoint.y() < 7)
        if (board[boardPoint.x()][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x(), boardPoint.y()+1));

    if(boardPoint.x() < 7 && boardPoint.y() < 7)
        if (board[boardPoint.x()+1][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()+1, boardPoint.y()+1));

    if(boardPoint.x() < 7)
        if (board[boardPoint.x()+1][boardPoint.y()] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()+1, boardPoint.y()));

    if(boardPoint.x() < 7 && boardPoint.y() > 0)
        if (board[boardPoint.x()+1][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()+1][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()+1, boardPoint.y()-1));

    if(boardPoint.y() > 0)
        if (board[boardPoint.x()][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x(), boardPoint.y()-1));

    if(boardPoint.x() > 0 && boardPoint.y() > 0)
        if (board[boardPoint.x()-1][boardPoint.y()-1] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()-1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()-1, boardPoint.y()-1));

    if(boardPoint.x() > 0)
        if (board[boardPoint.x()-1][boardPoint.y()] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()-1, boardPoint.y()));

    if(boardPoint.x() > 0 && boardPoint.y() < 7)
        if (board[boardPoint.x()-1][boardPoint.y()+1] == nullptr ||
            board[boardPoint.x()-1][boardPoint.y()+1]->figureColor == getOpponentColor(currentPlayerColor))
            possibleMoves.push_back(QPoint(boardPoint.x()-1, boardPoint.y()+1));
}

// function which tries to add consistently all possible moves in direction chosen by h - horizontal factor and v - vertical factor, v and h can be only 3 values (-1, 0, 1)
void ChessGameWidget::addAllPossibleMovesInDirection(Figure *figure, std::vector<QPoint>& possibleMoves, int h, int v)
{
    QPoint boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board
    int x, y, i = 1;

    while(true)
    {
        x = boardPoint.x() + h*i;
        y = boardPoint.y() + v*i;

        if(0 <= x && x <= 7 && 0 <= y && y <= 7)
        {
            if (board[x][y] == nullptr)
                possibleMoves.push_back(QPoint(x, y));

            else if (board[x][y]->figureColor == getOpponentColor(currentPlayerColor))
            {
                possibleMoves.push_back(QPoint(x, y));
                break;
            }
            else if (board[x][y]->figureColor == currentPlayerColor)
                break;
        }
        else
            break;
        i++;
    }
}

void ChessGameWidget::bishopPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves)
{
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, 1); // up right
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, -1); // down right
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, -1); // down left
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, 1); // up left
}

void ChessGameWidget::rookPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves)
{
    addAllPossibleMovesInDirection(figure, possibleMoves, 0, 1); // up
    addAllPossibleMovesInDirection(figure, possibleMoves, 1, 0); // right
    addAllPossibleMovesInDirection(figure, possibleMoves, 0, -1); // down
    addAllPossibleMovesInDirection(figure, possibleMoves, -1, 0); // left
}

void ChessGameWidget::queenPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves)
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

void ChessGameWidget::findPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves)
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
    case FigureType::Rook:
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

QPoint ChessGameWidget::pixelCoordinatesToBoardCoordinates(QPointF pixelCoordinates)
{
    return QPoint(pixelCoordinates.x() / SQUARE_SIZE, NUMBER_OF_SQUARES - (int) pixelCoordinates.y() / SQUARE_SIZE - 1);
}

QPointF ChessGameWidget::boardCoordinatesToPixelCoordinates(QPoint boardCoordinates)
{
    return QPointF(boardCoordinates.x() * SQUARE_SIZE, (NUMBER_OF_SQUARES - boardCoordinates.y() - 1) * SQUARE_SIZE);
}

PlayerColor ChessGameWidget::getOpponentColor(PlayerColor playerColor)
{
    return (PlayerColor) (1 - playerColor);
}

void ChessGameWidget::createPossibleMoveSquares(const std::vector<QPoint>& possibleMoves)
{
    foreach (QPoint possibleMovePoint, possibleMoves) {
        QPointF scenePoint = boardCoordinatesToPixelCoordinates(possibleMovePoint);
        possibleMoveSquares.push_back(new QGraphicsRectItem(scenePoint.x(), scenePoint.y(), SQUARE_SIZE, SQUARE_SIZE));
        possibleMoveSquares.back()->setBrush(QBrush(POSSIBLE_MOVE_FIELD_COLOR));
        possibleMoveSquares.back()->setZValue(0);
        chessScene.addItem(possibleMoveSquares.back());
    }
}

void ChessGameWidget::deletePossibleMoveSquares()
{
    foreach (QGraphicsRectItem *possibleMoveSquare, possibleMoveSquares) {
        chessScene.removeItem(possibleMoveSquare);
        delete possibleMoveSquare;
    }
    possibleMoveSquares.clear();
}
