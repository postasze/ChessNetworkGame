#ifndef CHESSGAMEWIDGET_H
#define CHESSGAMEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "constants.h"
#include "figure.h"
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
    void addFigureImagesToScene();
    QPoint pixelCoordinatesToBoardCoordinates(QPointF pixelCoordinates);
    QPointF boardCoordinatesToPixelCoordinates(QPoint boardCoordinates);
    void createPossibleMoveSquares(const std::vector<QPoint>& possibleMoves);
    void deletePossibleMoveSquares();
    PlayerColor getOpponentColor(PlayerColor playerColor);
    void promotePawn(Figure* promotedOne);

    QPixmap blackPawnPixmap, blackKnightPixmap, blackBishopPixmap, blackRookPixmap, blackQueenPixmap, blackKingPixmap;
    QPixmap whitePawnPixmap, whiteKnightPixmap, whiteBishopPixmap, whiteRookPixmap, whiteQueenPixmap, whiteKingPixmap;
    ExtendedGraphicsView chessView;
    QGraphicsScene chessScene;
    QGraphicsPixmapItem chessBoardPixmapItem;
    std::vector<Figure*> blackFigures, whiteFigures;
    std::vector<QGraphicsRectItem*> possibleMoveSquares;
    PlayerColor currentPlayerColor;
    Figure *draggedFigure;
    QPointF draggingStartPosition;
};

#endif // CHESSGAMEWIDGET_H
