#ifndef CHESSGAMEWIDGET_H
#define CHESSGAMEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "constants.h"
#include "figure.h"
#include "boardgraphicsitem.h"
#include "extendedgraphicsview.h"

class ChessGameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChessGameWidget(QWidget *parent = nullptr);
    ~ChessGameWidget();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:

public slots:

private:
    void loadFigureImages();
    void createFigures();
    void createBoard();
    void addFigureImagesToScene();
    std::vector<QPoint> findPossibleMoves(Figure *figure);
    QPoint pixelCoordinatesToBoardCoordinates(QPointF pixelCoordinates);
    QPointF boardCoordinatesToPixelCoordinates(QPoint boardCoordinates);

    QPixmap blackPawnPixmap, blackKnightPixmap, blackBishopPixmap, blackRookPixmap, blackQueenPixmap, blackKingPixmap;
    QPixmap whitePawnPixmap, whiteKnightPixmap, whiteBishopPixmap, whiteRookPixmap, whiteQueenPixmap, whiteKingPixmap;
    ExtendedGraphicsView chessView;
    QGraphicsScene chessScene;
    BoardGraphicsItem boardGraphicsItem;
    QGraphicsPixmapItem chessBoardPixmapItem;
    Figure* board[NUMBER_OF_SQUARES][NUMBER_OF_SQUARES];
    std::vector<Figure*> blackFigures, whiteFigures;
    PlayerColor currentPlayerColor;
    Figure* draggedFigure;
};

#endif // CHESSGAMEWIDGET_H
