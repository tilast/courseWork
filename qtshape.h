#ifndef QTSHAPE_H
#define QTSHAPE_H

#include "shape.h"
#include <QPainter>

template < typename T >
class QtShape : public Shape <T>
{
public:

    virtual void draw(QPainter & painter) const = 0;

    virtual void select(bool sel) {
        selected = sel;
    }
    virtual bool isSelected() const {
        return selected;
    }
    virtual bool isTopLeft(Point2D pressedPoint, Point2D epsilon) const = 0;
    virtual bool isBottomRight(Point2D pressedPoint, Point2D epsilon) const = 0;

protected:
    bool selected;
};

typedef QtShape< Point2D > QtShape2D;

#endif // QTSHAPE_H
