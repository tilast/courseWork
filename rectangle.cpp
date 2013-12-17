#include "rectangle.h"

Rectangle::Rectangle(const Point2D& p1, const Point2D& p2) {
    setBounds(p1, p2);
    setType();
}

void Rectangle::setBounds(const Point2D &p1, const Point2D &p2) {
    center = (p1 + p2) * 0.5;
    size = (p1 - p2).makePositive();
}
void Rectangle::move(const Point2D& destination) {
    center = destination;
}

void Rectangle::resize(const Point2D& destination, short t) {
    Point2D tl = center - size * 0.5;
    Point2D br = center + size * 0.5;
    Point2D tr;
    Point2D delta;
    tr.y = Rectangle::center.y - Rectangle::size.y * 0.5;
    tr.x = Rectangle::center.x + Rectangle::size.x * 0.5;
    Point2D bl;
    bl.y = Rectangle::center.y + Rectangle::size.y * 0.5;
    bl.x = Rectangle::center.x - Rectangle::size.x * 0.5;
    if(t == 0) {
        setBounds(destination, br);
    } else if(t == 1) {
        setBounds(tl, destination);
    } else if(t == 2) {
        tl.y = destination.y;
        br.x = destination.x;
        setBounds(tl, br);
    } else if(t == 3) {
        tl.x = destination.x;
        br.y = destination.y;
        setBounds(tl, br);
    }
}

void Rectangle::reflect(){
}

bool Rectangle::belongs(const Point2D& p) {
    Point2D p1 = center - size * 0.5;
    Point2D p2 = center + size * 0.5;

    return ((p1.x <= p.x) && (p1.y <= p.y) &&
            (p2.x >= p.x) && (p2.y >= p.y));
}

void Rectangle::setType() {
    type.x = 1.0;
}

int Rectangle::getType() {
    return (int)type.x;
}
