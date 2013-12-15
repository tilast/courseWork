#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent), selected(NULL), creating(false)
{
    epsilon.x = 50;
    epsilon.y = 50;
}

CanvasWidget::~CanvasWidget() {
    for (unsigned i = 0; i < shapes.size(); i++) {
        delete shapes[i];
    }
}

void CanvasWidget::selectAll() {
    selectedShapes.clear();
    for(auto iter = shapes.begin(); iter != shapes.end(); iter++) {
        selectedShapes.insert(*iter);
    }
}

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
                leftResize = true;
            } else if(selected->isBottomRight(pressedPoint, epsilon)) {
                rightResize = true;
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
            if(leftResize) {
                selected->resize(currentPoint, 0);
            } else if(rightResize) {
                selected->resize(currentPoint, 1);
            } else {
                selected->move(currentPoint - pressedPoint);
            }
        } else {
            creating = true;
            selected = new QtRectangle(pressedPoint, pressedPoint);
            shapes.push_back(selected);
            selected->select(true);
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
    leftResize = false;
    rightResize = false;
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
}
