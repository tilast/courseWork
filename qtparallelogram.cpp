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

    QPointF rect[5] = {
        QPointF(tl.x, tl.y),
        QPointF(b.x, b.y),
        QPointF(br.x, br.y),
        QPointF(d.x, d.y),
        QPointF(tl.x, tl.y),
    };

    painter.drawPolygon(points, 4);

    if(selected) {
        painter.setBrush(QBrush(QColor(255, 180, 120)));
        painter.drawEllipse(QPoint(tl.x, tl.y), 2, 2);
        painter.drawEllipse(QPoint(br.x, br.y), 2, 2);
        painter.drawEllipse(QPoint(a.x, a.y), 2, 2);

        QPen pen(Qt::green, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
        pen.setDashOffset(15.0);
        painter.setPen(pen);
        painter.drawPolyline(rect, 5);
    }
}

bool QtParallelogram::isTopLeft(Point2D pressedPoint, Point2D epsilon) const {
    Point2D tl = Parallelogram::center - Parallelogram::size * 0.5;
    Point2D minTL = tl - epsilon;
    Point2D maxTL = tl + epsilon;
    return ((pressedPoint.x > minTL.x) && (pressedPoint.y > minTL.y) && (pressedPoint.x < maxTL.x) && (pressedPoint.y < maxTL.y));
}

bool QtParallelogram::isControlPoint(Point2D pressedPoint, Point2D epsilon) const {
    Point2D tl = Parallelogram::center - Parallelogram::size * 0.5;
    Point2D cp;
    cp.x = tl.x + Parallelogram::controlPoint;
    cp.y = tl.y;

    qDebug() << "tl " << tl.x << " " << tl.y;
    qDebug() << "cp " << cp.x << " " << cp.y;

    Point2D minCP = cp - epsilon;
    Point2D maxCP = cp + epsilon;

    return ((pressedPoint.x > minCP.x) && (pressedPoint.y > minCP.y) && (pressedPoint.x < maxCP.x) && (pressedPoint.y < maxCP.y));
}

bool QtParallelogram::isBottomRight(Point2D pressedPoint, Point2D epsilon) const {
    Point2D br = Parallelogram::center + Parallelogram::size * 0.5;
    br.x += Parallelogram::controlPoint;
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
void QtParallelogram::resize(const Point2D& destination, short type) {
    Parallelogram::resize(destination, type);
}
bool QtParallelogram::belongs(const Point2D& p) {
    return Parallelogram::belongs(p);
}
