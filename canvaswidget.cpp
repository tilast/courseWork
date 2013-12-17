#include "canvaswidget.h"

#include <QDebug>
CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent), selected(NULL), creating(false)
{
    epsilon.x = 20;
    epsilon.y = 20;
    creatingType = 1;
    defaultOffsetParallelogram = 30.0;
    currentBackColor = Color(.5, .5, .5, 1);
    currentLineColor = Color(.0, .0, .5, 1);

    currentStyle.fillColor = currentBackColor;
    currentStyle.lineColor = currentLineColor;
    currentStyle.setStyle(currentLineColor);
}

CanvasWidget::~CanvasWidget() {
    for (unsigned i = 0; i < shapes.size(); i++) {
        delete shapes[i];
    }
}

void CanvasWidget::changeType(int type)
{
    creatingType = type;
}
void CanvasWidget::changeBackColor(int color)
{
    switch(color) {
        case 1 :
            currentBackColor = Color(1, 0, 0);
            break;
        case 2 :
            currentBackColor = Color(0, 1, 0);
            break;
        case 3 :
            currentBackColor = Color(0, 0, 1);
            break;
    }

    if(selected) {
        selected->getStyle().fillColor.setColor(currentBackColor);

        update();
    }
}
void CanvasWidget::changeLineColor(int color)
{
    switch(color) {
        case 1 :
            currentLineColor = Color(1, 0, 0);
            break;
        case 2 :
            currentLineColor = Color(0, 1, 0);
            break;
        case 3 :
            currentLineColor = Color(0, 0, 1);
            break;
    }

    if(selected) {
        selected->getStyle().lineColor.setColor(currentLineColor);
        update();
    }
}
void CanvasWidget::selectAll() {
    selectedShapes.clear();
    for(shapesContainer::iterator iter = shapes.begin(); iter != shapes.end(); iter++) {
        selectedShapes.insert(*iter);
    }}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {

    pressedPoint.x = event->localPos().x();
    pressedPoint.y = event->localPos().y();

    if(selected && keyPressed(Qt::Key_Control)) {
        selected->select(false);
    }
    selected = NULL;

    for(unsigned i = shapes.size(); i > 0; i--) {
        if(shapes[i - 1]->belongs(pressedPoint)) {
            toFront(i - 1);

            selected = shapes[shapes.size() - 1];
            selected->select(true);

            //Если не нажата клавиша CTRL, то выделение снимается, а выделяется только один элемент
            if(keyPressed(Qt::Key_Control))
                selectedShapes.clear();

            selectedShapes.insert(selected);

            qDebug() <<selectedShapes.size();

            if(selected->isTopLeft(pressedPoint, epsilon)) {
                topLeftResize = true;
            } else if(selected->isBottomRight(pressedPoint, epsilon)) {
                bottomRightResize = true;
            } else if(selected->isBottomLeft(pressedPoint, epsilon)) {
//                bottomLeftResize = true;
            } else if(selected->isTopRight(pressedPoint, epsilon)) {
//                topRightResize = true;
            }

            if(selected->getType() == 2) {
                if(((QtParallelogram*)selected)->isControlPoint(pressedPoint, epsilon)) {
                    controlPointModify = true;
                }
            }

            pressedPoint -= selected->getCenter();
            break;
        }
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {

    if((event->buttons()) & Qt::LeftButton) {
        Point2D currentPoint;
        currentPoint.x = event->localPos().x();
        currentPoint.y = event->localPos().y();

        if(creating) {
            shapes.back()->setBounds(pressedPoint, currentPoint);
        } else if(selected) {
            if(controlPointModify) {
                ((QtParallelogram*)selected)->setControlPoint(currentPoint.x);
            } else if(topLeftResize) {
                selected->resize(currentPoint, 0);
            } else if(bottomRightResize) {
                selected->resize(currentPoint, 1);
            } else if(topRightResize) {
                selected->resize(currentPoint, 2);
            } else if(bottomLeftResize) {
                selected->resize(currentPoint, 3);
            } else {
                selected->move(currentPoint - pressedPoint);
            }
        } else {
            creating = true;
            switch(creatingType) {
                case 2 :
                    selected = new QtParallelogram(pressedPoint, pressedPoint, defaultOffsetParallelogram);
                    break;
                case 1:
                    selected = new QtRectangle(pressedPoint, pressedPoint);
                    break;
            }

            selected->getStyle().lineColor.setColor(currentLineColor);
            selected->getStyle().fillColor.setColor(currentBackColor);
            shapes.push_back(selected);
            selected->select(true);

            /////////////////
            setModified(true);
        }

        update();
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *) {

    if(creating) {
        creating = false;
        selected->select(false);
        selected = NULL;
    }

    update();
    topLeftResize = false;
    bottomRightResize = false;
    topRightResize = false;
    bottomLeftResize = false;
    controlPointModify = false;
}

void CanvasWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    for(unsigned i =0; i < shapes.size(); i++) {
        shapes[i]->draw(painter);
    }
}

void CanvasWidget::toFront(int number) {
    int top = shapes.size() - 1;

    QtShape2D* tmp = shapes[number];
    shapes[number] = shapes[top];
    shapes[top] = tmp;

    /////////////////
    setModified(true);
}
