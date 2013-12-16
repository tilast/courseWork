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
#include "qtparallelogram.h"

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
    int creatingType;
    float defaultOffsetParallelogram;

    void changeType(int type);
    bool isModified() { return __isModified; }
    void setModified(bool flag) { __isModified = flag; }
    void selectAll();
    int pressedKeyCode;
signals:    
void modified();

public slots:

protected:

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void paintEvent(QPaintEvent * event);

    Point2D pressedPoint, epsilon;
    bool creating;

    bool leftResize, rightResize, controlPointModify;

    void toFront(int number);

private:
    bool __isModified;
    bool keyPressed(Qt::Key keyCode) { return (pressedKeyCode == 0 || pressedKeyCode != keyCode); }
};

#endif // CANVASWIDGET_H
