#ifndef QTPARALLELOGRAM_H
#define QTPARALLELOGRAM_H

#include "parallelogram.h"
#include "qtshape.h"
#include <QPainter>

class QtParallelogram : public Parallelogram, public QtShape2D {
public:
    QtParallelogram(const Point2D& p1, const Point2D& p2, const float& cp);
    QtParallelogram(const Point2D& p1, const Point2D& p2);
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
    bool isControlPoint(Point2D pressedPoint, Point2D epsilon) const;
    void setControlPoint(const float &cp);
    void setType();
    int getType();
    virtual QString svgElementCode() const;
};

#endif // QTPARALLELOGRAM_H
