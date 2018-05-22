#include "extendedgraphicsview.h"
#include <QMouseEvent>

ExtendedGraphicsView::ExtendedGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{

}

void ExtendedGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    event->ignore();
}

void ExtendedGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    event->ignore();
}

void ExtendedGraphicsView::dropEvent(QDropEvent *event)
{
    event->ignore();
}

void ExtendedGraphicsView::mousePressEvent(QMouseEvent *event)
{
    event->ignore();
}

void ExtendedGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();
}

void ExtendedGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
}

void ExtendedGraphicsView::wheelEvent(QWheelEvent *event)
{
    event->ignore();
}
