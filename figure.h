#ifndef FIGURE_H
#define FIGURE_H

#include "base.h"

class Figure
{
    public:
        virtual ~Figure();
        virtual DrawStyle& getStyle();
        virtual const DrawStyle& getStyle() const;
    protected:
        DrawStyle style;
};

#endif // FIGURE_H
