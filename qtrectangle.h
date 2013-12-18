#ifndef QTRECTANGLE_H
#define QTRECTANGLE_H

#include "rectangle.h"
#include "qtshape.h"
#include <QPainter>

class QtRectangle : public Rectangle, public QtShape2D {
public:
    QtRectangle(const Point2D& p1, const Point2D& p2);
    DrawStyle& getStyle();
    const DrawStyle& getStyle() const;
    Point2D getCenter() const;
    Point2D getSize() const;
    void setBounds(const Point2D& p1, const Point2D& p2);
    void move(const Point2D& destination);
    void resize(const Point2D& destination, short t);
    virtual void reflect();
    bool belongs(const Point2D& point);
    virtual void draw(QPainter & painter) const;
    void select(bool sel);
    bool isSelected() const;
    bool isTopLeft(Point2D pressedPoint, Point2D epsilon) const;
    bool isBottomRight(Point2D pressedPoint, Point2D epsilon) const;
    bool isTopRight(Point2D pressedPoint, Point2D epsilon) const;
    bool isBottomLeft(Point2D pressedPoint, Point2D epsilon) const;
    void setType();
    virtual int getType();
    virtual QString svgElementCode() const {
        Point2D center = getCenter();
        Point2D size = getSize();

        return QString("<rect x=\"%1\" y=\"%2\" width=\"%3\" height=\"%4\" style=\"fill:rgb(%5, %6, %7)\" />")
                .arg(center.x-size.x/2).arg(center.y-size.y/2).arg(size.x).arg(size.y)
                .arg(getStyle().fillColor.red*255).arg(getStyle().fillColor.green*255).arg(getStyle().fillColor.blue*255);;

    }
};

#endif // QTRECTANGLE_H
