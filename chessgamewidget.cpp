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
}

ChessGameWidget::~ChessGameWidget()
{
    foreach (Figure *figure, blackFigures) {
        delete figure;
    }
    blackFigures.clear();

    foreach (Figure *figure, whiteFigures) {
        delete figure;
    }
    whiteFigures.clear();
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
        chessScene.addItem(figure);

    foreach (Figure *figure, whiteFigures)
        chessScene.addItem(figure);
}

void ChessGameWidget::mousePressEvent(QMouseEvent *event)
{
    std::cout << "mousePressEvent" << std::endl;

    draggedFigure = dynamic_cast<Figure*>(chessScene.itemAt(event->pos(), QTransform()));
}

void ChessGameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "mouseReleaseEvent" << std::endl;
    if(draggedFigure != nullptr)
    {
        QPoint boardPoint = pixelCoordinatesToBoardCoordinates(event->pos());
        if(board[boardPoint.x()][boardPoint.y()] != nullptr)
        {

        }
        draggedFigure = nullptr;
    }
}

void ChessGameWidget::mouseMoveEvent(QMouseEvent *event)
{
    std::cout << "mouseMoveEvent" << std::endl;

    if(draggedFigure != nullptr)
        draggedFigure->setPos(event->pos() -= QPoint(SQUARE_SIZE / 2, SQUARE_SIZE / 2));
}

std::vector<QPoint> ChessGameWidget::findPossibleMoves(Figure *figure)
{
    std::vector<QPoint> possibleMoves;
    QPoint boardPoint = pixelCoordinatesToBoardCoordinates(figure->pos()); // position of figure on the board

    switch(figure->figureType)
    {
    case FigureType::Pawn:
        switch(figure->figureColor)
        {
        case PlayerColor::Black:
            if(boardPoint.y() == 0)
                return possibleMoves; // returning empty possible moves

            if(board[boardPoint.x()][boardPoint.y()-1] == nullptr)
                possibleMoves.push_back(QPoint(boardPoint.x(), boardPoint.y()-1));

            if(boardPoint.y() == 6 && board[boardPoint.x()][5] == nullptr && board[boardPoint.x()][4] == nullptr)
                possibleMoves.push_back(QPoint(boardPoint.x(), 4));
            break;
        case PlayerColor::White:
            if(boardPoint.y() == 7)
                return possibleMoves; // returning empty possible moves

            if(board[boardPoint.x()][boardPoint.y()+1] == nullptr)
                possibleMoves.push_back(QPoint(boardPoint.x(), boardPoint.y()+1));

            if(boardPoint.y() == 1 && board[boardPoint.x()][2] == nullptr && board[boardPoint.x()][3] == nullptr)
                possibleMoves.push_back(QPoint(boardPoint.x(), 3));
            break;
        }
        break;
    case FigureType::Knight:
        break;
    case FigureType::Bishop:
        break;
    case FigureType::Rook:
        break;
    case FigureType::Queen:
        break;
    case FigureType::King:
        break;
    }
}

QPoint ChessGameWidget::pixelCoordinatesToBoardCoordinates(QPointF pixelCoordinates)
{
    return QPoint(pixelCoordinates.x() / SQUARE_SIZE, pixelCoordinates.y() / SQUARE_SIZE);
}

QPointF ChessGameWidget::boardCoordinatesToPixelCoordinates(QPoint boardCoordinates)
{
    return boardCoordinates *= SQUARE_SIZE;
}
