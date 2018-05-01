#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsPixmapItem>
#include "constants.h"

class Figure : public QGraphicsPixmapItem
{
public:
    Figure(PlayerColor figureColor, FigureType figureType, const QPointF& scenePosition, const QPixmap& pixmap);
    Figure();

    FigureType figureType;
    PlayerColor figureColor;
private:
};

#endif // FIGURE_H
