#include "qtarrow.h"
#include <sstream>

#include <QDebug>

QtArrow::QtArrow(const Point2D& p1, const Point2D& p2, float coef) : Arrow(p1, p2, coef) {
}

bool QtArrow::getSide() const {
    return Arrow::getSide();
}

void QtArrow::setSide(bool s) {
    Arrow::setSide(s);
}

void QtArrow::reflect() {
    Arrow::reflect();
}

void QtArrow::draw(QPainter &painter) const {
    Point2D tl = Arrow::center - Arrow::size * 0.5;
    Point2D br = Arrow::center + Arrow::size * 0.5;
    Color p = getStyle().lineColor;
    Color f = getStyle().fillColor;
    if (isSelected()) f.alpha = 0.5;
    painter.setPen(QColor(p.red * 255, p.green * 255, p.blue * 255, p.alpha * 255));
    painter.setBrush(QBrush(QColor(f.red * 255, f.green * 255, f.blue * 255, f.alpha * 255)));

    Point2D leftPoint;
    leftPoint.x = tl.x;
    leftPoint.y = tl.y + (br.y - tl.y)*0.5;

    Point2D rightPoint;
    rightPoint.x = br.x;
    rightPoint.y = tl.y + (br.y - tl.y)*0.5;

    Point2D topTip, bottomTip;
    if(Arrow::getSide()) {
        topTip.y = tl.y;
        topTip.x = br.x - Arrow::size.x*tipCoef;

        bottomTip.y = br.y;
        bottomTip.x = br.x - Arrow::size.x*tipCoef;
        painter.drawLine(QPointF(leftPoint.x, leftPoint.y), QPointF(rightPoint.x, rightPoint.y));
        painter.drawLine(QPointF(topTip.x, topTip.y), QPointF(rightPoint.x, rightPoint.y));
        painter.drawLine(QPointF(bottomTip.x, bottomTip.y), QPointF(rightPoint.x, rightPoint.y));
    } else {
        topTip.y = tl.y;
        topTip.x = tl.x + Arrow::size.x*tipCoef;

        bottomTip.y = br.y;
        bottomTip.x = tl.x + Arrow::size.x*tipCoef;
        painter.drawLine(QPointF(leftPoint.x, leftPoint.y), QPointF(rightPoint.x, rightPoint.y));
        painter.drawLine(QPointF(topTip.x, topTip.y), QPointF(leftPoint.x, leftPoint.y));
        painter.drawLine(QPointF(bottomTip.x, bottomTip.y), QPointF(leftPoint.x, leftPoint.y));
    }

    if(selected) {
        painter.setBrush(QBrush(QColor(255, 180, 120)));
        painter.drawEllipse(QPoint(tl.x, tl.y), 2, 2);
        painter.drawEllipse(QPoint(br.x, br.y), 2, 2);
    }
}

bool QtArrow::isTopLeft(Point2D pressedPoint, Point2D epsilon) const {
    Point2D tl = Arrow::center - Arrow::size * 0.5;
    Point2D minTL = tl - epsilon;
    Point2D maxTL = tl + epsilon;
    return ((pressedPoint.x > minTL.x) && (pressedPoint.y > minTL.y) && (pressedPoint.x < maxTL.x) && (pressedPoint.y < maxTL.y));
}

bool QtArrow::isBottomRight(Point2D pressedPoint, Point2D epsilon) const {
    Point2D br = Arrow::center + Arrow::size * 0.5;
    Point2D minBR = br - epsilon;
    Point2D maxBR = br + epsilon;
    return ((pressedPoint.x > minBR.x) && (pressedPoint.y > minBR.y) && (pressedPoint.x < maxBR.x) && (pressedPoint.y < maxBR.y));
}
bool QtArrow::isTopRight(Point2D pressedPoint, Point2D epsilon) const {
    Point2D tr;
    tr.y = Arrow::center.y - Arrow::size.y * 0.5;
    tr.x = Arrow::center.x + Arrow::size.x * 0.5;
    Point2D minTR = tr - epsilon;
    Point2D maxTR = tr + epsilon;
    return ((pressedPoint.x > minTR.x) && (pressedPoint.y > minTR.y) && (pressedPoint.x < maxTR.x) && (pressedPoint.y < maxTR.y));
}

bool QtArrow::isBottomLeft(Point2D pressedPoint, Point2D epsilon) const {
    Point2D bl;
    bl.y = Arrow::center.y + Arrow::size.y * 0.5;
    bl.x = Arrow::center.x - Arrow::size.x * 0.5;
    Point2D minBL = bl - epsilon;
    Point2D maxBL = bl + epsilon;
    return ((pressedPoint.x > minBL.x) && (pressedPoint.y > minBL.y) && (pressedPoint.x < maxBL.x) && (pressedPoint.y < maxBL.y));
}

void QtArrow::select(bool sel) {
    QtShape2D::select(sel);
}
bool QtArrow::isSelected() const {
    return QtShape2D::isSelected();
}
DrawStyle& QtArrow::getStyle() {
    return Arrow::getStyle();
}
const DrawStyle& QtArrow::getStyle() const {
    return Arrow::getStyle();
}
Point2D QtArrow::getCenter() const {
    return Arrow::getCenter();
}
Point2D QtArrow::getSize() const {
    return Arrow::getSize();
}
void QtArrow::setBounds(const Point2D& p1, const Point2D& p2) {
    Arrow::setBounds(p1, p2);
}
void QtArrow::move(const Point2D& destination) {
    Arrow::move(destination);
}
void QtArrow::resize(const Point2D& destination, short t) {
    Arrow::resize(destination, t);
}
bool QtArrow::belongs(const Point2D& p) {
    return Arrow::belongs(p);
}
void QtArrow::setType() {
    Arrow::setType();
}

int QtArrow::getType() {
    return Arrow::getType();
}

QString QtArrow::svgElementCode() const {
    return QString("")
            .append("<arrow>")
            .append("")
            .append("</arrow>");
}
