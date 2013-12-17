#ifndef ZIGZAG_H
#define ZIGZAG_H

#include "shape.h"

class Zigzag : public Shape2D
{
protected:
    int pointsAmount;
public:
    Zigzag(const Point2D& p1, const Point2D& p2, const int& pa);
    Zigzag(const Point2D& p1, const Point2D& p2);
    virtual void setBounds(const Point2D& p1, const Point2D& p2);
    virtual void move(const Point2D& destination);
    virtual void resize(const Point2D& destination, short t);
    virtual bool belongs(const Point2D& point);
    virtual void setPointsAmount(const int& pa);
    virtual void setType();
    virtual int getType();
};

#endif // ZIGZAG_H
