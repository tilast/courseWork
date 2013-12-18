#include "qtzigzag.h"

#include <QDebug>

QtZigzag::QtZigzag(const Point2D& p1, const Point2D& p2, const int& pa) : Zigzag(p1, p2, pa) {
}

QtZigzag::QtZigzag(const Point2D& p1, const Point2D& p2) : Zigzag(p1, p2) {
    setPointsAmount(6);
}

void QtZigzag::draw(QPainter &painter) const {
    Point2D tl = Zigzag::center - Zigzag::size * 0.5;
    Point2D br = Zigzag::center + Zigzag::size * 0.5;
    Color p = getStyle().lineColor;
    Color f = getStyle().fillColor;
    if (isSelected()) f.alpha = 0.5;
    painter.setPen(QColor(p.red * 255, p.green * 255, p.blue * 255, p.alpha * 255));
    painter.setBrush(QBrush(QColor(f.red * 255, f.green * 255, f.blue * 255, f.alpha * 255)));

    float partLine = (br.x - tl.x) / (float)pointsAmount;

    QPointF *points = new QPointF[pointsAmount];

    for(int i = 0; i < pointsAmount; i++) {

        points[i].setX(tl.x + i*partLine);

        if (i % 2) {
            points[i].setY(tl.y);
        } else {
            points[i].setY(br.y);
        }
    }

    painter.drawPolyline(points, pointsAmount);

    if(selected) {
        painter.setBrush(QBrush(QColor(255, 180, 120)));
        painter.drawEllipse(QPoint(tl.x, tl.y), 2, 2);
        painter.drawEllipse(QPoint(br.x, br.y), 2, 2);

    }
}
void QtZigzag::reflect() {

}

bool QtZigzag::isTopLeft(Point2D pressedPoint, Point2D epsilon) const {
    Point2D tl = Zigzag::center - Zigzag::size * 0.5;
    Point2D minTL = tl - epsilon;
    Point2D maxTL = tl + epsilon;
    return ((pressedPoint.x > minTL.x) && (pressedPoint.y > minTL.y) && (pressedPoint.x < maxTL.x) && (pressedPoint.y < maxTL.y));
}
bool QtZigzag::isTopRight(Point2D pressedPoint, Point2D epsilon) const {
    return false;
}

bool QtZigzag::isBottomLeft(Point2D pressedPoint, Point2D epsilon) const {
    return false;
}


bool QtZigzag::isBottomRight(Point2D pressedPoint, Point2D epsilon) const {
    Point2D br = Zigzag::center + Zigzag::size * 0.5;
    Point2D minBR = br - epsilon;
    Point2D maxBR = br + epsilon;
    return ((pressedPoint.x > minBR.x) && (pressedPoint.y > minBR.y) && (pressedPoint.x < maxBR.x) && (pressedPoint.y < maxBR.y));
}

void QtZigzag::select(bool sel) {
    QtShape2D::select(sel);
}
bool QtZigzag::isSelected() const {
    return QtShape2D::isSelected();
}
DrawStyle& QtZigzag::getStyle() {
    return Zigzag::getStyle();
}
const DrawStyle& QtZigzag::getStyle() const {
    return Zigzag::getStyle();
}
Point2D QtZigzag::getCenter() const {
    return Zigzag::getCenter();
}
Point2D QtZigzag::getSize() const {
    return Zigzag::getSize();
}
void QtZigzag::setBounds(const Point2D& p1, const Point2D& p2) {
    Zigzag::setBounds(p1, p2);
}
void QtZigzag::move(const Point2D& destination) {
    Zigzag::move(destination);
}
void QtZigzag::resize(const Point2D& destination, short t) {
    Zigzag::resize(destination, t);
}
bool QtZigzag::belongs(const Point2D& p) {
    return Zigzag::belongs(p);
}
void QtZigzag::setType() {
    Zigzag::setType();
}

int QtZigzag::getType() {
    return Zigzag::getType();
}
QString QtZigzag::svgElementCode() const {
    Point2D tl = Zigzag::center - Zigzag::size * 0.5;
    Point2D br = Zigzag::center + Zigzag::size * 0.5;
    Color p = getStyle().lineColor;
    float partLine = (br.x - tl.x) / (float)pointsAmount;

    QString stream = QString("<polyline points=\"");
    float x, y;
    for(int i = 0; i < pointsAmount; i++) {
        x = tl.x + i*partLine;
        if (i % 2) {
            y = tl.y;
        } else {
            y = br.y;
        }

        stream.append("%1,%2 ");
        stream = stream.arg((int)x).arg((int)y);
    }

    stream.append("\" style=\"fill:none;stroke:rgb(%1,%2,%3);stroke-width:2\" />");
    stream = stream.arg(p.red*255).arg(p.green*255).arg(p.blue*255);

    return stream;
}

