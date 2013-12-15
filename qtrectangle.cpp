#include "qtrectangle.h"

QtRectangle::QtRectangle(const Point2D& p1, const Point2D& p2) : Rectangle(p1, p2) {
}

void QtRectangle::draw(QPainter &painter) const {
    Point2D tl = Rectangle::center - Rectangle::size * 0.5;
    Point2D br = Rectangle::center + Rectangle::size * 0.5;
    Color p = getStyle().lineColor;
    Color f = getStyle().fillColor;
    if (isSelected()) f.alpha = 0.5;
    painter.setPen(QColor(p.red * 255, p.green * 255, p.blue * 255, p.alpha * 255));
    painter.setBrush(QBrush(QColor(f.red * 255, f.green * 255, f.blue * 255, f.alpha * 255)));
    painter.drawRect(tl.x, tl.y, Rectangle::size.x, Rectangle::size.y);
    if(selected) {
        painter.setBrush(QBrush(QColor(255, 180, 120)));
        painter.drawEllipse(QPoint(tl.x, tl.y), 2, 2);
        painter.drawEllipse(QPoint(br.x, br.y), 2, 2);
    }
}

bool QtRectangle::isTopLeft(Point2D pressedPoint, Point2D epsilon) const {
    Point2D tl = Rectangle::center - Rectangle::size * 0.5;
    Point2D minTL = tl - epsilon;
    Point2D maxTL = tl + epsilon;
    return ((pressedPoint.x > minTL.x) && (pressedPoint.y > minTL.y) && (pressedPoint.x < maxTL.x) && (pressedPoint.y < maxTL.y));
}

bool QtRectangle::isBottomRight(Point2D pressedPoint, Point2D epsilon) const {
    Point2D br = Rectangle::center + Rectangle::size * 0.5;
    Point2D minBR = br - epsilon;
    Point2D maxBR = br + epsilon;
    return ((pressedPoint.x > minBR.x) && (pressedPoint.y > minBR.y) && (pressedPoint.x < maxBR.x) && (pressedPoint.y < maxBR.y));
}

void QtRectangle::select(bool sel) {
    QtShape2D::select(sel);
}
bool QtRectangle::isSelected() const {
    return QtShape2D::isSelected();
}
DrawStyle& QtRectangle::getStyle() {
    return Rectangle::getStyle();
}
const DrawStyle& QtRectangle::getStyle() const {
    return Rectangle::getStyle();
}
Point2D QtRectangle::getCenter() const {
    return Rectangle::getCenter();
}
Point2D QtRectangle::getSize() const {
    return Rectangle::getSize();
}
void QtRectangle::setBounds(const Point2D& p1, const Point2D& p2) {
    Rectangle::setBounds(p1, p2);
}
void QtRectangle::move(const Point2D& destination) {
    Rectangle::move(destination);
}
void QtRectangle::resize(const Point2D& destination, short type) {
    Rectangle::resize(destination, type);
}
bool QtRectangle::belongs(const Point2D& p) {
    return Rectangle::belongs(p);
}
