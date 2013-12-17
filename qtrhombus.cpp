#include "qtrhombus.h"

QtRhombus::QtRhombus(const Point2D &p1, const Point2D &p2) : QtRectangle(p1, p2) {}

void QtRhombus::draw(QPainter &painter) const {
    Point2D tl = Rectangle::center - Rectangle::size * 0.5;
    Point2D br = Rectangle::center + Rectangle::size * 0.5;

    Color p = getStyle().lineColor;
    Color f = getStyle().fillColor;
    if (isSelected()) f.alpha = 0.5;
    painter.setPen(QColor(p.red * 255, p.green * 255, p.blue * 255, p.alpha * 255));
    painter.setBrush(QBrush(QColor(f.red * 255, f.green * 255, f.blue * 255, f.alpha * 255)));

    qDebug() << "tl: " << tl.x << " " << tl.y;
    qDebug() << "br: " << br.x << " " << br.y;

    Point2D a;
    a.x = tl.x + (br.x - tl.x)*0.5;
    a.y = tl.y;
    qDebug() << "a: " << a.x << " " << a.y;

    Point2D b;
    b.x = br.x;
    b.y = tl.y + (br.y - tl.y)*0.5;
    qDebug() << "b: " << b.x << " " << b.y;

    Point2D c;
    c.x = tl.x + (br.x - tl.x)*0.5;
    c.y = br.y;
    qDebug() << "c: " << c.x << " " << c.y;

    Point2D d;
    d.x = tl.x;
    d.y = tl.y + (br.y - tl.y)*0.5;
    qDebug() << "d: " << d.x << " " << d.y;

    QPointF points[4] = {
        QPointF(a.x, a.y),
        QPointF(b.x, b.y),
        QPointF(c.x, c.y),
        QPointF(d.x, d.y)
    };

    painter.drawPolygon(points, 4);

    if(selected) {
        painter.setBrush(QBrush(QColor(255, 180, 120)));
        painter.drawEllipse(QPoint(tl.x, tl.y), 2, 2);
        painter.drawEllipse(QPoint(br.x, br.y), 2, 2);
    }
}

QString QtRhombus::svgElementCode() const {
    Point2D center = getCenter();
    Point2D size = getSize();

    Point2D left = center, right = center, top = center, bottom = center;

    left.x -= size.x/2;
    right.x += size.x/2;
    top.y += size.y/2;
    bottom.y -= size.y/2;

    return QString("<polygon points=\"%1,%2  %3,%4 %5,%6  %7,%8\" style=\"fill:rgb(%9, %10, %11)\" abki=\"rhombus\" />")
            .arg(left.x).arg(left.y)
            .arg(top.x).arg(top.y)
            .arg(right.x).arg(right.y)
            .arg(bottom.x).arg(bottom.y)
            .arg(getStyle().fillColor.red*255).arg(getStyle().fillColor.green*255).arg(getStyle().fillColor.blue*255);
}
