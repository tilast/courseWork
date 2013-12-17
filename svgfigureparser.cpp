#include "svgfigureparser.h"

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

}

QtParallelogram *SVGFigureParser::parseParallelogram(const QDomElement &e)
{
//    <polygon points=\"1,1.0  2.0,3.0 1.0,4.0 1.0,5.0\" style=\"fill:rgb(255, 126.7, 33.5)\" abki=\"parallelogram\" />
//    points: lt , rt , rb , lb

    if (e.tagName() != "polygon" || e.attribute("abki") != "parallelogram")
        return NULL;

    QStringList points = parsePoints(e.attribute("points"));
    qDebug() <<points;
    if(points.size() != 8) //8 points coordinates + 1 - full string
        return NULL;
    qDebug() <<"Parse points";
    Point2D leftTop(points[6].toFloat(),points[1].toFloat());
    Point2D rightBottom(points[4].toFloat(),points[5].toFloat());
    float cp = points[0].toFloat()-points[6].toFloat();
    return new QtParallelogram(leftTop, rightBottom, cp);
}
