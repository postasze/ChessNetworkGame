#ifndef BOARDGRAPHICSITEM_H
#define BOARDGRAPHICSITEM_H

#include <QtWidgets>
#include "constants.h"

class BoardGraphicsItem : public QGraphicsItem
{
public:
    BoardGraphicsItem();
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BOARDGRAPHICSITEM_H
