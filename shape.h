#ifndef SHAPE_H
#define SHAPE_H

#include "figure.h"
#include <QDebug>

template < typename T >
class Shape: public Figure
{
public:
    virtual T getCenter() const { return center; }
    virtual T getSize() const { return size; }
    virtual void setBounds(const T& p1, const T& p2) = 0;
    virtual void move(const T& destination) = 0;
    virtual bool belongs(const T& point) = 0;
    virtual void resize(const T& destination, short t) = 0;
    virtual void reflect() = 0;
    virtual void setType() = 0;
    virtual int getType() = 0;
protected:
    T center;
    T size;
    T type;
};

typedef Shape< Point2D > Shape2D;

#endif // SHAPE_H
