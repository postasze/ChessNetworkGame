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
    void createBoard();
    void addFigureImagesToScene();
    PlayerColor getOpponentColor(PlayerColor playerColor);
    QPoint pixelCoordinatesToBoardCoordinates(QPointF pixelCoordinates);
    QPointF boardCoordinatesToPixelCoordinates(QPoint boardCoordinates);
    void findPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves);
    void addAllPossibleMovesInDirection(Figure *figure, std::vector<QPoint>& possibleMoves, int h, int v);
    void pawnPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves);
    void knightPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves);
    void bishopPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves);
    void rookPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves);
    void queenPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves);
    void kingPossibleMoves(Figure *figure, std::vector<QPoint>& possibleMoves);
    void promotePawn(Figure* promotedOne);
    void createPossibleMoveSquares(const std::vector<QPoint>& possibleMoves);
    void deletePossibleMoveSquares();
    void eraseForbiddenKingMoves(std::vector<QPoint>& possibleMoves);

    QPixmap blackPawnPixmap, blackKnightPixmap, blackBishopPixmap, blackRookPixmap, blackQueenPixmap, blackKingPixmap;
    QPixmap whitePawnPixmap, whiteKnightPixmap, whiteBishopPixmap, whiteRookPixmap, whiteQueenPixmap, whiteKingPixmap;
    ExtendedGraphicsView chessView;
    QGraphicsScene chessScene;
    QGraphicsPixmapItem chessBoardPixmapItem;
    Figure* board[NUMBER_OF_SQUARES][NUMBER_OF_SQUARES];
    std::vector<Figure*> blackFigures, whiteFigures;
    std::vector<QGraphicsRectItem*> possibleMoveSquares;
    PlayerColor currentPlayerColor;
    Figure *draggedFigure;
    QPointF draggingStartPosition;
    std::vector<QPoint> possibleMoves;
    std::vector<QPoint> forbiddenKingMoves;


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

#endif // CHESSGAMEWIDGET_H
