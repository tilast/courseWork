#include "canvaswidget.h"

#include <QDebug>
CanvasWidget::CanvasWidget(QWidget *parent) :
    QWidget(parent), selected(NULL), transformation(NONE)
{
    epsilon.x = 20;
    epsilon.y = 20;
    creatingType = 1;
    zigzagPointsAmount = 5;
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
    qDebug() <<"Change back color";
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
    qDebug() <<selected;
    if (!selectedShapes.empty())
        for(const auto &shape: selectedShapes) {
            (&*shape)->getStyle().fillColor.setColor(currentBackColor);
        }
    update();
}

void CanvasWidget::changeBackColor(QColor backColor)
{
    currentBackColor = Color(backColor.red()/255.0,backColor.green()/255.0,backColor.blue()/255.0);
    if (!selectedShapes.empty())
        for(const auto &shape: selectedShapes) {
            (&*shape)->getStyle().lineColor.setColor(currentBackColor);
        }
    update();
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
    if (!selectedShapes.empty())
        for(const auto &shape: selectedShapes) {
            (&*shape)->getStyle().lineColor.setColor(currentLineColor);
        }
    update();
}

void CanvasWidget::changeLineColor(QColor lineColor)
{
    currentLineColor = Color(lineColor.red()/255.0,lineColor.green()/255.0,lineColor.blue()/255.0);
    if (!selectedShapes.empty())
        for(const auto &shape: selectedShapes) {
            (&*shape)->getStyle().lineColor.setColor(currentLineColor);
        }
    update();
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
                topLeftResize = true;
            } else if(selected->isBottomRight(pressedPoint, epsilon)) {
                bottomRightResize = true;
            } else if(selected->isBottomLeft(pressedPoint, epsilon)) {
               bottomLeftResize = true;
            } else if(selected->isTopRight(pressedPoint, epsilon)) {
               topRightResize = true;
                // transformation = LEFT_RESIZE;
            }
            //Проверяем нажатие на контроллек масштабирования (правый нижний)
            // else if(selected->isBottomRight(pressedPoint, epsilon)){
            //     transformation = RIGHT_RESIZE;
            // }

            if (transformation == LEFT_RESIZE || transformation == RIGHT_RESIZE) //Оставляем только одну выделенную фигуру6 которую хотим масштабировать
                clearSelectedShapes();
            if (havingShapeInSelectedShapes(selected))
                transformation = MOVING;
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
                for(const auto &shape: selectedShapes) //foreach Loop
                {
                    (&*shape)->move((&*shape)->getCenter()-selected->getCenter() + currentPoint - pressedPoint);
                }
// =======
//             if(transformation == LEFT_RESIZE) {
//                 selected->resize(currentPoint, 0);
//             } else if(transformation == RIGHT_RESIZE) {
//                 selected->resize(currentPoint, 1);
//             } else if(controlPointModify) {
//                 ((QtParallelogram*)selected)->setControlPoint(currentPoint.x);
//             } else if (transformation == MOVING) {
//                 for(const auto &shape: selectedShapes) //foreach Loop
//                 {
//                     (&*shape)->move((&*shape)->getCenter()-selected->getCenter() + currentPoint - pressedPoint);
//                 }
//>>>>>>> 58591d064c3b898ae4671dd70530a81f8dfeff03
            }

        } else {
            qDebug() << "creating type: " << creatingType;
            transformation = CREATING;
            switch(creatingType) {
                case 2 :
                    selected = new QtParallelogram(pressedPoint, pressedPoint, defaultOffsetParallelogram);
                    break;
                case 1:
                    selected = new QtRectangle(pressedPoint, pressedPoint);
                    break;
                case 3:
                    selected = new QtRhombus(pressedPoint, pressedPoint);
                    break;
                case 4:
                    selected = new QtZigzag(pressedPoint, pressedPoint, zigzagPointsAmount);
                    break;
                case 5:
                    selected = new QtArrow(pressedPoint, pressedPoint);
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

    topLeftResize = false;
    bottomRightResize = false;
    topRightResize = false;
    bottomLeftResize = false;


    controlPointModify = false;
    selected = NULL;
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

void CanvasWidget::reflect() {
    for(const auto &shape: selectedShapes) //foreach Loop
    {
        (&*shape)->reflect();
    }
    update();
}

void CanvasWidget::setZigzagPointAmount(int amount) {
    zigzagPointsAmount = amount;

    for(const auto &shape: selectedShapes) //foreach Loop
    {
        qDebug() << "all is okay ";
        if((&*shape)->getType() == 4) {
            ((QtZigzag*)(&*shape))->setPointsAmount(amount);
            update();
        }
    }
}
