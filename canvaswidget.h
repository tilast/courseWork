#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QDebug>

#include <vector>
#include <set>
#include "qtshape.h"
#include "qtrectangle.h"

typedef std::vector<QtShape2D*> shapesContainer;
typedef std::set<QtShape2D*> selectedShapesContainer;

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0);
    ~CanvasWidget();

    shapesContainer shapes;
    selectedShapesContainer selectedShapes;

    QtShape2D* selected;

    int pressedKeyCode;

    bool isModified() { return __isModified; }

signals:
    
public slots:

protected:

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void paintEvent(QPaintEvent * event);

    Point2D pressedPoint, epsilon;
    bool creating;

    bool leftResize, rightResize;

    void toFront(int number);

private:
    bool __isModified;
};

#endif // CANVASWIDGET_H
