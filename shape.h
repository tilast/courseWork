#ifndef SHAPE_H
#define SHAPE_H

#include "figure.h"

template < typename T >
class Shape: public Figure
{
    public:
        virtual T getCenter() const { return center; }
        virtual T getSize() const { return size; }
        virtual void setBounds(const T& p1, const T& p2) = 0;
        virtual void move(const T& destination) = 0;
        virtual bool belongs(const T& point) = 0;
        virtual void resize(const T& destination, short type) = 0;

    protected:
        T center;
        T size;
};

typedef Shape< Point2D > Shape2D;

#endif // SHAPE_H