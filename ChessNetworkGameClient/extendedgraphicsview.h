#ifndef EXTENDEDGRAPHICSVIEW_H
#define EXTENDEDGRAPHICSVIEW_H

#include <QGraphicsView>

class ExtendedGraphicsView : public QGraphicsView
{
public:
    ExtendedGraphicsView(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // EXTENDEDGRAPHICSVIEW_H
