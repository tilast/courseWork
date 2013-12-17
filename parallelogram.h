#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "shape.h"

class Parallelogram : public Shape2D
{
protected:
    float controlPoint;
public:
    Parallelogram(const Point2D& p1, const Point2D& p2, const float& cp);
    Parallelogram(const Point2D& p1, const Point2D& p2);
    virtual void setBounds(const Point2D& p1, const Point2D& p2);
    virtual void setControlPoint(const float& cp);
    virtual void move(const Point2D& destination);
    virtual void resize(const Point2D& destination, short t);
    virtual void reflect();
    virtual bool belongs(const Point2D& point);
    virtual void setType();
    virtual int getType();
};

#endif // PARALLELOGRAM_H
