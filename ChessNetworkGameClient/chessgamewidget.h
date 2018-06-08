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

    void createPossibleMoveSquares(const std::vector<QPoint>& possibleMoves);
    void makeMove(QPoint startPoint, QPoint destinationPoint);

    PlayerColor playerColor; // color of this client on the table
    bool inGame;
    std::vector<QPoint> possibleMoves;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void playerFigurePressed(QPoint);
    void playerHasMoved(QPoint);

public slots:

private:
    void loadFigureImages();
    void createFigures();
    void addFigureImagesToScene();
    QPoint pixelCoordinatesToBoardCoordinates(QPointF pixelCoordinates);
    QPointF boardCoordinatesToPixelCoordinates(QPoint boardCoordinates);
    void deletePossibleMoveSquares();
    PlayerColor getOpponentColor(PlayerColor playerColor);
    void promotePawn(Figure* promotedOne);
    Figure* getFigureWithCoordinates(QPoint figurePosition);
    Figure* getPlayerFigureWithCoordinates(PlayerColor playerColor, QPoint figurePosition);
    void removeFigure(Figure *figure);

    QPixmap blackPawnPixmap, blackKnightPixmap, blackBishopPixmap, blackRookPixmap, blackQueenPixmap, blackKingPixmap;
    QPixmap whitePawnPixmap, whiteKnightPixmap, whiteBishopPixmap, whiteRookPixmap, whiteQueenPixmap, whiteKingPixmap;
    ExtendedGraphicsView chessView;
    QGraphicsScene chessScene;
    QGraphicsPixmapItem chessBoardPixmapItem;
    std::vector<Figure*> blackFigures, whiteFigures;
    std::vector<QGraphicsRectItem*> possibleMoveSquares;
    PlayerColor currentPlayerColor; // color of the client who makes move now
    Figure *draggedFigure;
    QPointF draggingStartPosition;
};

#endif // CHESSGAMEWIDGET_H
