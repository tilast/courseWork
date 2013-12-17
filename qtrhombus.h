#ifndef QTRHOMBUS_H
#define QTRHOMBUS_H

#include "qtrectangle.h"

class QtRhombus : public QtRectangle
{
public:
    QtRhombus(const Point2D& p1, const Point2D& p2);
    void draw(QPainter & painter) const;
    QString svgElementCode() const;
};

#endif // QTRHOMBUS_H
