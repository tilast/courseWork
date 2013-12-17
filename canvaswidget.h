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
#include "qtrhombus.h"
#include "qtzigzag.h"
#include "qtarrow.h"

typedef std::vector<QtShape2D*> shapesContainer;
typedef std::set<QtShape2D*> selectedShapesContainer;

enum CanvasWidgetActionType {NONE = 0,CREATING = 1, MOVING = 2, LEFT_RESIZE = 3, RIGHT_RESIZE = 4, CONTROL_POINT_MODIFY = 5};

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0);
    ~CanvasWidget();

    shapesContainer shapes;
    selectedShapesContainer selectedShapes;

    void clearSelectedShapes();
    void insertShapeInSelectedShapes(QtShape2D* shape);
    bool havingShapeInSelectedShapes(QtShape2D* shape);
    QtShape2D* selected;

    int creatingType;
    float defaultOffsetParallelogram;

    Color currentLineColor;
    Color currentBackColor;
    DrawStyle currentStyle;
    int zigzagPointsAmount;

    void changeType(int type);

    void changeBackColor(int color);
    void changeBackColor(QColor backColor);
    void changeLineColor(int color);
    void changeLineColor(QColor lineColor);
    void reflect();
    bool isModified() { return __isModified; }
    void setModified(bool flag) { __isModified = flag; }
    void selectAll();
    void setZigzagPointAmount(int amount);
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


    bool topLeftResize, bottomRightResize, topRightResize, bottomLeftResize, controlPointModify;

    CanvasWidgetActionType transformation;


    void toFront(int number);

private:
    bool __isModified;
    bool isKeyPressed(Qt::Key keyCode) { return (pressedKeyCode != 0 && pressedKeyCode == keyCode); }
};

#endif // CANVASWIDGET_H
