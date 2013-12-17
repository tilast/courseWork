#ifndef QTZIGZAG_H
#define QTZIGZAG_H

#include "zigzag.h"
#include "qtshape.h"
#include <QPainter>

class QtZigzag : public Zigzag, public QtShape2D {
public:
    QtZigzag(const Point2D& p1, const Point2D& p2, const int& pa);
    QtZigzag(const Point2D& p1, const Point2D& p2);
    DrawStyle& getStyle();
    const DrawStyle& getStyle() const;
    Point2D getCenter() const;
    Point2D getSize() const;
    void setBounds(const Point2D& p1, const Point2D& p2);
    void move(const Point2D& destination);
    void resize(const Point2D& destination, short t);
    bool belongs(const Point2D& point);
    void draw(QPainter & painter) const;
    void select(bool sel);
    bool isSelected() const;
    bool isTopLeft(Point2D pressedPoint, Point2D epsilon) const;
    bool isBottomRight(Point2D pressedPoint, Point2D epsilon) const;
    bool isTopRight(Point2D pressedPoint, Point2D epsilon) const;
    bool isBottomLeft(Point2D pressedPoint, Point2D epsilon) const;
    void setType();
    int getType();
    virtual QString svgElementCode() const;
};

#endif // QTZIGZAG_H
