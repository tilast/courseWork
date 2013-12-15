#ifndef QTRECTANGLE_H
#define QTRECTANGLE_H

#include "rectangle.h"
#include "qtshape.h"
#include <QPainter>

class QtRectangle : public Rectangle, public QtShape2D {
public:
    QtRectangle(const Point2D& p1, const Point2D& p2);
    virtual DrawStyle& getStyle();
    virtual const DrawStyle& getStyle() const;
    virtual Point2D getCenter() const;
    virtual Point2D getSize() const;
    virtual void setBounds(const Point2D& p1, const Point2D& p2);
    virtual void move(const Point2D& destination);
    virtual void resize(const Point2D& destination, short type);
    virtual bool belongs(const Point2D& point);
    virtual void draw(QPainter & painter) const;
    virtual void select(bool sel);
    virtual bool isSelected() const;
    virtual bool isTopLeft(Point2D pressedPoint, Point2D epsilon) const;
    virtual bool isBottomRight(Point2D pressedPoint, Point2D epsilon) const;
    virtual QString svgElementCode() const {
        Point2D center = getCenter();
        Point2D size = getSize();

        return QString("<rect x=\"%1\" y=\"%2\" width=\"%3\" height=\"%4\" />").arg(center.x-size.x/2).arg(center.y-size.y/2).arg(size.x).arg(size.y);

    }
};

#endif // QTRECTANGLE_H
