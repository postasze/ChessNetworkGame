#include "boardgraphicsitem.h"

BoardGraphicsItem::BoardGraphicsItem()
{

}

QRectF BoardGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

QPainterPath BoardGraphicsItem::shape() const
{
    QPainterPath painterPath;
    for(int i = 0; i < NUMBER_OF_SQUARES; i++)
        for(int j = 0; j < NUMBER_OF_SQUARES; j++)
            if((i + j) % 2 == 0)
                painterPath.addRect(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);

    return painterPath;
}

void BoardGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillPath(shape(), BRIGHT_FIELD_COLOR);
}
