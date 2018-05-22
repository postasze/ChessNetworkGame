#include "figure.h"

Figure::Figure(PlayerColor figureColor, FigureType figureType,  const QPointF& scenePosition, const QPixmap& pixmap) :
    QGraphicsPixmapItem(pixmap), figureColor(figureColor), figureType(figureType)
{
    this->setPos(scenePosition);
}

Figure::Figure()
{

}
