#include "canvaswidget.h"

#include <QDebug>
CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent), selected(NULL), transformation(NONE)
{
    epsilon.x = 50;
    epsilon.y = 50;
    creatingType = 1;
    defaultOffsetParallelogram = 30.0;
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

void CanvasWidget::clearSelectedShapes()
{
    for(const auto &shape: shapes) {
        (&*shape)->select(false);
    }
    selectedShapes.clear();
}
void CanvasWidget::insertShapeInSelectedShapes(QtShape2D* shape)
{
    shape->select(true);
    selectedShapes.insert(shape);
}

bool CanvasWidget::havingShapeInSelectedShapes(QtShape2D* shape) {
    size_t oldSize = selectedShapes.size();
    selectedShapesContainer tmpCont = selectedShapes;
    tmpCont.insert(shape);
    return oldSize == tmpCont.size();
}

void CanvasWidget::selectAll()
{
    clearSelectedShapes();
    for(const auto &shape: shapes) {
        (&*shape)->select(true);
        selectedShapes.insert(&*shape);
    }
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {

    pressedPoint.x = event->localPos().x();
    pressedPoint.y = event->localPos().y();

    selected = NULL;
    transformation = NONE;
    for(unsigned i = shapes.size(); i > 0; i--) {
        if(shapes[i - 1]->belongs(pressedPoint)) {
            //Нажали на фигуру
            toFront(i - 1); //переместилю фигуру вперед
            selected = shapes[shapes.size() - 1]; //Запоминаем последню выбранную фигуры

            //Проверяем нажатие на контроллер масштабирования (левый верхний)
            if(selected->isTopLeft(pressedPoint, epsilon)) {
                transformation = LEFT_RESIZE;
            }
            //Проверяем нажатие на контроллек масштабирования (правый нижний)
            else if(selected->isBottomRight(pressedPoint, epsilon)){
                transformation = RIGHT_RESIZE;
            }

            if (transformation == LEFT_RESIZE || transformation == RIGHT_RESIZE) //Оставляем только одну выделенную фигуру6 которую хотим масштабировать
                clearSelectedShapes();

            if (havingShapeInSelectedShapes(selected))
                transformation = MOVING;
            else
                insertShapeInSelectedShapes(selected);

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

        if(transformation == CREATING) {
            shapes.back()->setBounds(pressedPoint, currentPoint);
        } else if(selected) {
            if(transformation == LEFT_RESIZE) {
                selected->resize(currentPoint, 0);
            } else if(transformation == RIGHT_RESIZE) {
                selected->resize(currentPoint, 1);
            } else if(controlPointModify) {
                ((QtParallelogram*)selected)->setControlPoint(currentPoint.x);
            } else if (transformation == MOVING) {
                for(const auto &shape: selectedShapes) //foreach Loop
                {
                    (&*shape)->move((&*shape)->getCenter()-selected->getCenter() + currentPoint - pressedPoint);
                }
            }

        } else {
            transformation = CREATING;
            switch(creatingType) {
                case 2 :
                    selected = new QtParallelogram(pressedPoint, pressedPoint, defaultOffsetParallelogram);
                    break;
                case 1:
                    selected = new QtRectangle(pressedPoint, pressedPoint);
                    break;
            }

            shapes.push_back(selected);
            selected->select(true);

            /////////////////
            setModified(true);
        }

        update();
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (selected == NULL) { //Нажатие на пустую область. Снимаем выдиление
        clearSelectedShapes();
    }
    if (transformation == MOVING) {}
    else if(transformation == CREATING or !isKeyPressed(Qt::Key_Control) and selected != NULL) { //Оставляем 1 выделенную фигуру: конец создания фигуры, нажатие без Ctrl
        clearSelectedShapes();
        insertShapeInSelectedShapes(selected);
    }

    update();
    controlPointModify = false;
    transformation = NONE;
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
