#include "parallelogram.h"

Parallelogram::Parallelogram(const Point2D& p1, const Point2D& p2, const float& cp) {
    setControlPoint(cp);
    setBounds(p1, p2);
    setType();
}
Parallelogram::Parallelogram(const Point2D& p1, const Point2D& p2) {
    setBounds(p1, p2);
    setType();
}

void Parallelogram::setBounds(const Point2D &p1, const Point2D &p2) {
    center = (p1 + p2) * 0.5;
    size = (p1 - p2).makePositive();
}
void Parallelogram::move(const Point2D& destination) {
    center = destination;
}

void Parallelogram::resize(const Point2D& destination, short t) {
    Point2D p1 = center - size * 0.5;
    Point2D p2 = center + size * 0.5;
    Point2D test = destination;
    if(t) {
        setBounds(p1, test);
    } else {
        setBounds(test, p2);
    }
}

bool Parallelogram::belongs(const Point2D& p) {
    Point2D p1 = center - size * 0.5;
    Point2D p2 = center + size * 0.5;
    p1.x -= fabs(controlPoint);
    p2.x += fabs(controlPoint);

    return ((p1.x <= p.x) && (p1.y <= p.y) &&
            (p2.x >= p.x) && (p2.y >= p.y));
}
void Parallelogram::setControlPoint(const float &cp) {
    Point2D tl = center - size * 0.5;
    controlPoint = cp - tl.x;
}

void Parallelogram::setType() {
    type.x = 2.0;
}

int Parallelogram::getType() {
    return (int)type.x;
}
