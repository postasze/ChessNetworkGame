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
    addFigureImagesToScene();

    draggedFigure = nullptr;
    currentPlayerColor = PlayerColor::White;
    playerColor = PlayerColor::None;
    inGame = false;
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

void ChessGameWidget::createFigures()//
{
    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; ++i) //
        whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::Pawn, QPointF(i * SQUARE_SIZE, 6 * SQUARE_SIZE), whitePawnPixmap));

    for(unsigned int i = 0; i < NUMBER_OF_SQUARES; ++i)
        blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::Pawn, QPointF(i * SQUARE_SIZE, 1 * SQUARE_SIZE), blackPawnPixmap));

    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::LeftRook, QPointF(0 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteRookPixmap));
    whiteFigures.push_back(new Figure(PlayerColor::White, FigureType::RightRook, QPointF(7 * SQUARE_SIZE, 7 * SQUARE_SIZE), whiteRookPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::LeftRook, QPointF(0 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackRookPixmap));
    blackFigures.push_back(new Figure(PlayerColor::Black, FigureType::RightRook, QPointF(7 * SQUARE_SIZE, 0 * SQUARE_SIZE), blackRookPixmap));
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
    //std::cout << "mousePressEvent" << std::endl;

    if(!inGame)
        return;

    if(currentPlayerColor != playerColor)
        return;

    if(draggedFigure != nullptr)
        return;

    QPoint boardPoint = pixelCoordinatesToBoardCoordinates(event->pos());
    draggedFigure = dynamic_cast<Figure*>(chessScene.itemAt(event->pos(), QTransform()));

    if(draggedFigure != nullptr && draggedFigure->figureColor == currentPlayerColor)
    {
        emit playerFigurePressed(boardPoint);
        //findPossibleMoves(draggedFigure, possibleMoves);
        //createPossibleMoveSquares(possibleMoves);
        draggingStartPosition = draggedFigure->pos();
    }
    else
        draggedFigure = nullptr;
}

void ChessGameWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //std::cout << "mouseReleaseEvent" << pixelCoordinatesToBoardCoordinates(event->pos()).x()<<pixelCoordinatesToBoardCoordinates(event->pos()).y()<< std::endl;

    if(!inGame)
        return;

    if(currentPlayerColor != playerColor)
        return;

    if(draggedFigure != nullptr)
    {
        QPoint boardPoint = pixelCoordinatesToBoardCoordinates(event->pos());

        if(std::find(possibleMoves.begin(), possibleMoves.end(), boardPoint) == possibleMoves.end())
        {
            deletePossibleMoveSquares();
            draggedFigure->setPos(draggingStartPosition); // situation when move is invalid
            draggedFigure = nullptr;
        }
        else // situation when move is valid
            emit playerHasMoved(boardPoint);
    }
}

void ChessGameWidget::mouseMoveEvent(QMouseEvent *event)
{
    //std::cout << "mouseMoveEvent" << std::endl;

    if(!inGame)
        return;

    if(currentPlayerColor != playerColor)
        return;

    if(draggedFigure != nullptr)
        draggedFigure->setPos(event->pos() -= QPoint(SQUARE_SIZE / 2, SQUARE_SIZE / 2));
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
    switch(playerColor)
    {
    case PlayerColor::Black:
        return PlayerColor::White;
        break;
    case PlayerColor::White:
        return PlayerColor::Black;
        break;
    }
    return PlayerColor::None;
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

void ChessGameWidget::promotePawn(Figure* promotedOne)
{
    promotedOne->figureType = FigureType::Queen;
    QPixmap newPixmap = promotedOne->figureColor == PlayerColor::Black ? blackQueenPixmap : whiteQueenPixmap;
    promotedOne->setPixmap(newPixmap);
}

void ChessGameWidget::makeMove(QPoint startPoint, QPoint destinationPoint)
{
    QPointF destinationScenePosition = boardCoordinatesToPixelCoordinates(destinationPoint);
    Figure *selectedFigure, *figureAtDestination;

    if(draggedFigure != nullptr)
        selectedFigure = draggedFigure;
    else
        selectedFigure = getPlayerFigureWithCoordinates(currentPlayerColor, startPoint);

    figureAtDestination = getPlayerFigureWithCoordinates(currentPlayerColor, destinationPoint);

    if(figureAtDestination != nullptr && figureAtDestination->figureType == FigureType::RightRook) // short castling
    {
        QPoint newRookPoint = destinationPoint - QPoint(2, 0);
        QPoint newKingPoint = destinationPoint - QPoint(1, 0);

        selectedFigure->setPos(boardCoordinatesToPixelCoordinates(newKingPoint));
        figureAtDestination->setPos(boardCoordinatesToPixelCoordinates(newRookPoint));
    }
    else if(figureAtDestination != nullptr && figureAtDestination->figureType == FigureType::LeftRook) // long castling
    {
        QPoint newRookPoint = destinationPoint + QPoint(3, 0);
        QPoint newKingPoint = destinationPoint + QPoint(2, 0);

        selectedFigure->setPos(boardCoordinatesToPixelCoordinates(newKingPoint));
        figureAtDestination->setPos(boardCoordinatesToPixelCoordinates(newRookPoint));
    }
    else
    {
        figureAtDestination = getPlayerFigureWithCoordinates(getOpponentColor(currentPlayerColor), destinationPoint);
        if(figureAtDestination != nullptr)
            removeFigure(figureAtDestination);

        selectedFigure->setPos(destinationScenePosition);
    }

    //promote pawn, if reached end of the board
    if (selectedFigure->figureType == FigureType::Pawn && (destinationPoint.x() == 7 || destinationPoint.y() == 0))
        promotePawn(selectedFigure);

    currentPlayerColor = getOpponentColor(currentPlayerColor);
    deletePossibleMoveSquares();
    draggedFigure = nullptr;
}

Figure* ChessGameWidget::getFigureWithCoordinates(QPoint figurePosition)
{
    QPointF figureScenePosition = boardCoordinatesToPixelCoordinates(figurePosition);
    std::vector<Figure*>::iterator figureIterator;

    figureIterator = std::find_if(blackFigures.begin(), blackFigures.end(),
        [figureScenePosition](Figure *figure) {return figure->pos() == figureScenePosition;});
    if(figureIterator != blackFigures.end())
        return *figureIterator;
    figureIterator = std::find_if(whiteFigures.begin(), whiteFigures.end(),
        [figureScenePosition](Figure *figure) {return figure->pos() == figureScenePosition;});
    if(figureIterator != whiteFigures.end())
        return *figureIterator;

    return nullptr;
}

Figure* ChessGameWidget::getPlayerFigureWithCoordinates(PlayerColor playerColor, QPoint figurePosition)
{
    QPointF figureScenePosition = boardCoordinatesToPixelCoordinates(figurePosition);
    std::vector<Figure*>::iterator figureIterator;

    switch(playerColor)
    {
    case PlayerColor::Black:
        figureIterator = std::find_if(blackFigures.begin(), blackFigures.end(),
            [figureScenePosition](Figure *figure) {return figure->pos() == figureScenePosition;});
        if(figureIterator != blackFigures.end())
            return *figureIterator;
        else
            return nullptr;
        break;
    case PlayerColor::White:
        figureIterator = std::find_if(whiteFigures.begin(), whiteFigures.end(),
            [figureScenePosition](Figure *figure) {return figure->pos() == figureScenePosition;});
        if(figureIterator != whiteFigures.end())
            return *figureIterator;
        else
            return nullptr;
        break;
    }
    return nullptr;
}

void ChessGameWidget::removeFigure(Figure *figure)
{
    chessScene.removeItem(figure);

    switch(figure->figureColor)
    {
    case PlayerColor::Black:
        blackFigures.erase(std::find(blackFigures.begin(), blackFigures.end(), figure));
        break;
    case PlayerColor::White:
        whiteFigures.erase(std::find(whiteFigures.begin(), whiteFigures.end(), figure));
        break;
    }
    delete figure;
}
