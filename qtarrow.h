#ifndef QTARROW_H
#define QTARROW_H

#include "arrow.h"
#include "qtshape.h"
#include <QPainter>

class QtArrow : public Arrow, public QtShape2D {
public:
    QtArrow(const Point2D& p1, const Point2D& p2);
    DrawStyle& getStyle();
    const DrawStyle& getStyle() const;
    Point2D getCenter() const;
    Point2D getSize() const;
    void setBounds(const Point2D& p1, const Point2D& p2);
    void move(const Point2D& destination);
    void resize(const Point2D& destination, short t);
    void reflect();
    void setSide(bool s);
    bool getSide() const;
    bool belongs(const Point2D& point);
    virtual void draw(QPainter & painter) const;
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

#endif // QTARROW_H
