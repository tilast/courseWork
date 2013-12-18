#include "svgfigureparser.h"
#include <cmath>

QStringList SVGFigureParser::parsePoints(const QString &string)
{
    QRegExp rx("\[\\s\]*(\[\\d\\.\]+)\[\\s\]*,\[\\s\]*(\[\\d\\.\]+)\[\\s\]*(\[\\d\\.\]+)\[\\s\]*,\[\\s\]*(\[\\d\\.\]+)\[\\s\]*(\[\\d\\.\]+)\[\\s\]*,\[\\s\]*(\[\\d\\.\]+)\[\\s\]*(\[\\d\\.\]+)\[\\s\]*,\[\\s\]*(\[\\d\\.\]+)\[\\s\]*");
    QStringList list;
    if (!checkRegExp(rx))
        return list;
    if (rx.indexIn(string) != -1) {
        list = rx.capturedTexts();
        list.pop_front();
    }
    return list;
}

QtRectangle* SVGFigureParser::parseRect(const QDomElement &e)
{
        if (e.tagName() != "rect")
            return NULL;

        double height = e.attribute("height").toDouble();
        double width = e.attribute("width").toDouble();
        double x = e.attribute("x").toDouble();
        double y = e.attribute("y").toDouble();
        Point2D first(x,y);
        Point2D second(x+width,y+height);

        return new QtRectangle(first, second);
}

QtShape2D *SVGFigureParser::parsePolygon(const QDomElement &e)
{
    if (e.tagName() != "polygon")
        return NULL;
    if (e.attribute("abki") == "parallelogram")
        return parseParallelogram(e);
    if (e.attribute("abki") == "rhombus")
        return parseRhombus(e);
    return NULL;

}

QtParallelogram *SVGFigureParser::parseParallelogram(const QDomElement &e)
{
//    <polygon points=\"1,1.0  2.0,3.0 1.0,4.0 1.0,5.0\" style=\"fill:rgb(255, 126.7, 33.5)\" abki=\"parallelogram\" />
//    points: lt , rt , rb , lb

    if (e.tagName() != "polygon" || e.attribute("abki") != "parallelogram")
        return NULL;

    QStringList points = parsePoints(e.attribute("points"));
    qDebug() <<points;
    if(points.size() != 8) //8 points coordinates
        return NULL;
    qDebug() <<"Parse points";
    Point2D leftTop(points[6].toFloat(),points[1].toFloat());
    Point2D rightBottom(points[4].toFloat(),points[5].toFloat());
    float cp = points[0].toFloat()-points[6].toFloat();
    return new QtParallelogram(leftTop, rightBottom, cp);
}

QtRhombus *SVGFigureParser::parseRhombus(const QDomElement &e)
{
//    <polygon points=\"%1,%2  %3,%4 %5,%6  %7,%8\" style=\"fill:rgb(%9, %10, %11)\" abki=\"rhombus\" />
//    points: left , top , right , bottom
    if (e.tagName() != "polygon" || e.attribute("abki") != "rhombus")
        return NULL;

    QStringList points = parsePoints(e.attribute("points"));
    if(points.size() != 8) //8 points coordinates
        return NULL;
    Point2D leftTop(points[0].toFloat(),points[3].toFloat());
    Point2D rightBottom(points[4].toFloat(),points[7].toFloat());
    return new QtRhombus(leftTop, rightBottom);
}

QtZigzag *SVGFigureParser::parseCurve(const QDomElement &e)
{
//    <polyline points="442,145 500,37 558,145 616,37 674,145 " style="fill:none;stroke:rgb(0,0,0);stroke-width:2" />
    if (e.tagName() != "polyline" || e.attribute("points").isEmpty())
        return NULL;
    QStringList points = parsePoints(e.attribute("points"));
    if (points.size() < 4) //min 2 point
        return NULL;
    Point2D left(points[0].toFloat(), points[1].toFloat());
    float pa = points[2].toFloat()-points[0].toFloat();
    Point2D right(points[0].toFloat() + std::ceil(points.size()/2)*pa, points[3].toFloat());

    return new QtZigzag(left,right,pa);
}

QtArrow *SVGFigureParser::parseArrow(const QDomElement &element)
{

}
