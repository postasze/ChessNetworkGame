#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsPixmapItem>
#include "constants.h"

class Figure : public QGraphicsPixmapItem
{
public:
    Figure(PlayerColor figureColor, FigureType figureType, const QPointF& scenePosition, const QPixmap& pixmap);
    Figure();

    PlayerColor figureColor;
    FigureType figureType;

private:

};


#endif // FIGURE_H
