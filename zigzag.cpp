#include "zigzag.h"

Zigzag::Zigzag(const Point2D& p1, const Point2D& p2, const int& pa) {
    setBounds(p1, p2);
    setType();
    setPointsAmount(pa);
}
Zigzag::Zigzag(const Point2D& p1, const Point2D& p2) {
    setBounds(p1, p2);
    setType();
    setPointsAmount(5);
}

void Zigzag::setBounds(const Point2D &p1, const Point2D &p2) {
    center = (p1 + p2) * 0.5;
    size = (p1 - p2).makePositive();
}
void Zigzag::move(const Point2D& destination) {
    center = destination;
}

void Zigzag::resize(const Point2D& destination, short t) {
    Point2D p1 = center - size * 0.5;
    Point2D p2 = center + size * 0.5;
    Point2D test = destination;
    if(t) {
        setBounds(p1, test);
    } else {
        setBounds(test, p2);
    }
}

bool Zigzag::belongs(const Point2D& p) {
    Point2D p1 = center - size * 0.5;
    Point2D p2 = center + size * 0.5;

    return ((p1.x <= p.x) && (p1.y <= p.y) &&
            (p2.x >= p.x) && (p2.y >= p.y));
}
void Zigzag::setPointsAmount(const int &pa) {
    pointsAmount = pa;
}

void Zigzag::setType() {
    type.x = 4.0;
}

int Zigzag::getType() {
    return (int)type.x;
}
