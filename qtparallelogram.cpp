#include "qtparallelogram.h"

#include <QDebug>

QtParallelogram::QtParallelogram(const Point2D& p1, const Point2D& p2, const float& cp) : Parallelogram(p1, p2, cp) {
}

QtParallelogram::QtParallelogram(const Point2D& p1, const Point2D& p2) : Parallelogram(p1, p2) {
    setControlPoint(25.);
}

void QtParallelogram::draw(QPainter &painter) const {
    Point2D tl = Parallelogram::center - Parallelogram::size * 0.5;
    Color p = getStyle().lineColor;
    Color f = getStyle().fillColor;
    if (isSelected()) f.alpha = 0.5;
    painter.setPen(QColor(p.red * 255, p.green * 255, p.blue * 255, p.alpha * 255));
    painter.setBrush(QBrush(QColor(f.red * 255, f.green * 255, f.blue * 255, f.alpha * 255)));

    Point2D a;
    a.x = tl.x + Parallelogram::controlPoint;
    a.y = tl.y;

    Point2D br = Parallelogram::center + Parallelogram::size * 0.5;
    br.x += Parallelogram::controlPoint;

    Point2D b;
    b.x = br.x;
    b.y = tl.y;

    Point2D c;
    c.x = br.x - Parallelogram::controlPoint;
    c.y = br.y;

    Point2D d;
    d.x = tl.x;
    d.y = br.y;

    QPointF points[4] = {
        QPointF(a.x, a.y),
        QPointF(b.x, b.y),
        QPointF(c.x, c.y),
        QPointF(d.x, d.y)
    };

    painter.drawPolygon(points, 4);

    if(selected) {
        painter.setBrush(QBrush(QColor(255, 180, 120)));
        painter.drawEllipse(QPoint(tl.x, tl.y), 2, 2);
        painter.drawEllipse(QPoint(c.x, c.y), 2, 2);
        painter.drawEllipse(QPoint(a.x, a.y), 2, 2);

    }
}

bool QtParallelogram::isTopLeft(Point2D pressedPoint, Point2D epsilon) const {
    Point2D tl = Parallelogram::center - Parallelogram::size * 0.5;
    Point2D minTL = tl - epsilon;
    Point2D maxTL = tl + epsilon;
    return ((pressedPoint.x > minTL.x) && (pressedPoint.y > minTL.y) && (pressedPoint.x < maxTL.x) && (pressedPoint.y < maxTL.y));
}
bool QtParallelogram::isTopRight(Point2D pressedPoint, Point2D epsilon) const {
    return false;
}

bool QtParallelogram::isBottomLeft(Point2D pressedPoint, Point2D epsilon) const {
    return false;
}

bool QtParallelogram::isControlPoint(Point2D pressedPoint, Point2D epsilon) const {
    Point2D tl = Parallelogram::center - Parallelogram::size * 0.5;
    Point2D cp;
    cp.x = tl.x + Parallelogram::controlPoint;
    cp.y = tl.y;

    Point2D minCP = cp - epsilon;
    Point2D maxCP = cp + epsilon;

    return ((pressedPoint.x > minCP.x) && (pressedPoint.y > minCP.y) && (pressedPoint.x < maxCP.x) && (pressedPoint.y < maxCP.y));
}

bool QtParallelogram::isBottomRight(Point2D pressedPoint, Point2D epsilon) const {
    Point2D br = Parallelogram::center + Parallelogram::size * 0.5;
    Point2D minBR = br - epsilon;
    Point2D maxBR = br + epsilon;
    return ((pressedPoint.x > minBR.x) && (pressedPoint.y > minBR.y) && (pressedPoint.x < maxBR.x) && (pressedPoint.y < maxBR.y));
}

void QtParallelogram::select(bool sel) {
    QtShape2D::select(sel);
}
bool QtParallelogram::isSelected() const {
    return QtShape2D::isSelected();
}
DrawStyle& QtParallelogram::getStyle() {
    return Parallelogram::getStyle();
}
const DrawStyle& QtParallelogram::getStyle() const {
    return Parallelogram::getStyle();
}
Point2D QtParallelogram::getCenter() const {
    return Parallelogram::getCenter();
}
Point2D QtParallelogram::getSize() const {
    return Parallelogram::getSize();
}
void QtParallelogram::setBounds(const Point2D& p1, const Point2D& p2) {
    Parallelogram::setBounds(p1, p2);
}
void QtParallelogram::setControlPoint(const float& cp) {
    Parallelogram::setControlPoint(cp);
}
void QtParallelogram::move(const Point2D& destination) {
    Parallelogram::move(destination);
}
void QtParallelogram::resize(const Point2D& destination, short t) {
    Parallelogram::resize(destination, t);
}
bool QtParallelogram::belongs(const Point2D& p) {
    return Parallelogram::belongs(p);
}
void QtParallelogram::setType() {
    Parallelogram::setType();
}

int QtParallelogram::getType() {
    return Parallelogram::getType();
}
QString QtParallelogram::svgElementCode() const {
    Point2D tl = Parallelogram::center - Parallelogram::size * 0.5;

    Point2D a;
    a.x = tl.x + Parallelogram::controlPoint;
    a.y = tl.y;

    Point2D br = Parallelogram::center + Parallelogram::size * 0.5;
    br.x += Parallelogram::controlPoint;

    Point2D b;
    b.x = br.x;
    b.y = tl.y;

    Point2D c;
    c.x = br.x - Parallelogram::controlPoint;
    c.y = br.y;

    Point2D d;
    d.x = tl.x;
    d.y = br.y;

    return QString("<polygon points=\"%1,%2  %3,%4 %5,%6  %7,%8\" style=\"fill:rgb(%9, %10, %11)\" />")
            .arg(a.x).arg(a.y)
            .arg(b.x).arg(b.y)
            .arg(c.x).arg(c.y)
            .arg(d.x).arg(d.y)
            .arg(getStyle().fillColor.red*255).arg(getStyle().fillColor.green*255).arg(getStyle().fillColor.blue*255);
}
