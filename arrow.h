#ifndef ARROW_H
#define ARROW_H

#include "shape.h"

class Arrow : public Shape2D
{
protected:
    float tipCoef;
    bool side;
public:
    Arrow(const Point2D& p1, const Point2D& p2);
    virtual void setBounds(const Point2D& p1, const Point2D& p2);
    virtual void move(const Point2D& destination);
    virtual void resize(const Point2D& destination, short t);
    virtual bool belongs(const Point2D& point);
    virtual void setType();
    virtual int getType();
    virtual void setTipCoef(float& coef);
    virtual float getTipCoef();
    virtual void reflect();
    virtual void setSide(bool s);
    virtual bool getSide() const;
};

#endif // ARROW_H
