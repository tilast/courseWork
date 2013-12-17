#include "arrow.h"

Arrow::Arrow(const Point2D& p1, const Point2D& p2) {
    setBounds(p1, p2);
    setType();
}

void Arrow::setBounds(const Point2D &p1, const Point2D &p2) {
    center = (p1 + p2) * 0.5;
    size = (p1 - p2).makePositive();
}
void Arrow::move(const Point2D& destination) {
    center = destination;
}

void Arrow::resize(const Point2D& destination, short t) {
    Point2D tl = center - size * 0.5;
    Point2D br = center + size * 0.5;
    Point2D tr;
    Point2D delta;
    tr.y = Arrow::center.y - Arrow::size.y * 0.5;
    tr.x = Arrow::center.x + Arrow::size.x * 0.5;
    Point2D bl;
    bl.y = Arrow::center.y + Arrow::size.y * 0.5;
    bl.x = Arrow::center.x - Arrow::size.x * 0.5;
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

bool Arrow::belongs(const Point2D& p) {
    Point2D p1 = center - size * 0.5;
    Point2D p2 = center + size * 0.5;

    return ((p1.x <= p.x) && (p1.y <= p.y) &&
            (p2.x >= p.x) && (p2.y >= p.y));
}

void Arrow::setType() {
    type.x = 5.0;
}

int Arrow::getType() {
    return (int)type.x;
}

void Arrow::setTipCoef(float& coef) {
    tipCoef = coef;
}

float Arrow::getTipCoef() {
    return tipCoef;
}
