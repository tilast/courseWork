#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <vector>
#include "qtshape.h"
#include "qtrectangle.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0);
    ~CanvasWidget();

    std::vector<QtShape2D*> shapes;
    QtShape2D* selected;

signals:
    
public slots:

protected:

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void paintEvent(QPaintEvent * event);

    Point2D pressedPoint;
    bool creating;
};

#endif // CANVASWIDGET_H
