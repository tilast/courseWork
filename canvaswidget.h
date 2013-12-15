#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
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

    bool isModified() { return __isModified; }

signals:
    
public slots:

protected:

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void paintEvent(QPaintEvent * event);

    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);

    Point2D pressedPoint, epsilon;
    bool creating;

    bool leftResize, rightResize;

    void toFront(int number);

private:
    bool __isModified;
};

#endif // CANVASWIDGET_H
