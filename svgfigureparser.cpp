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
    Point2D left(points[0].toFloat(), points[3].toFloat());
    float delta = points[4].toFloat()-points[2].toFloat();
//    delta /= 2;
    float pa = points.size();

    Point2D right(points[0].toFloat() + delta * pa, points[1].toFloat());

    return new QtZigzag(left,right,pa);
}

QtArrow *SVGFigureParser::parseArrow(const QDomElement &e)
{
//    <arrow>
//        <line x1="527" y1="389" x2="804" y2="389" style="stroke:rgb(0,0,0);stroke-width:2" />
//        <line x1="748.6" y1="341" x2="804" y2="389" style="stroke:rgb(0,0,0);stroke-width:1" />
//        <line x1="748.6" y1="437" x2="804" y2="389" style="stroke:rgb(0,0,0);stroke-width:1" />
//    </arrow>
    if (e.tagName() != "arrow")
        return NULL;
    QDomNodeList lineList = e.childNodes();
    bool side = e.attribute("side").toInt();
    qDebug() <<lineList.size();

    float x1 = lineList.at(0).toElement().attribute("x1").toFloat();
    float x2 = lineList.at(0).toElement().attribute("x2").toFloat();
    float y2 = lineList.at(0).toElement().attribute("y2").toFloat();

    float x3 = lineList.at(1).toElement().attribute("x1").toFloat();
    float y3 = lineList.at(1).toElement().attribute("y1").toFloat();

    float y5 = lineList.at(2).toElement().attribute("y1").toFloat();
    Point2D leftPoint(x1, y3);
    Point2D rightPoint(x2, y2);
    Point2D tl(x1, y3);
    Point2D br(x2, y5);
    float delta = x2 - x3;
    //float length = x2 - x1; - unused variable

    //float c = delta / length; - unused variable

    qDebug() << delta << " delta";

    Point2D first(x1,y3);
    Point2D second(x2,y5);
    float coef = (x2-x3)/(x2-x1);
    QtArrow * arrow = (side) ? new QtArrow(first, second, coef) : new QtArrow(second, first, 1 - coef);

    if(!side) {
        arrow->setSide(side);
    }

    return arrow;
}
