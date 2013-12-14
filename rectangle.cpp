#include "rectangle.h"

Rectangle::Rectangle(const Point2D& p1, const Point2D& p2) {
    setBounds(p1, p2);
}

void Rectangle::setBounds(const Point2D &p1, const Point2D &p2) {
    center = (p1 + p2) * 0.5;
    size = (p1 - p2).makePositive();
}
void Rectangle::move(const Point2D& destination) {
    center = destination;
}

bool Rectangle::belongs(const Point2D& p) {
    Point2D p1 = center - size * 0.5;
    Point2D p2 = center + size * 0.5;

    return ((p1.x <= p.x) && (p1.y <= p.y) &&
            (p2.x >= p.x) && (p2.y >= p.y));
}
