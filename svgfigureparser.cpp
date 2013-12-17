#include "svgfigureparser.h"

QStringList SVGFigureParser::parsePoints(const QString &string)
{
    QRegExp rx("\[\\s\]*\[\\d\\.\]\[\\s\]*,\[\\s\]*\[\\d\\.\]\[\\s\]*\[\\d\\.\]\[\\s\]*,\[\\s\]*\[\\d\\.\]\[\\s\]*\[\\d\\.\]\[\\s\]*,\[\\s\]*\[\\d\\.\]\[\\s\]*");
    QStringList list;
    if (!checkRegExp(rx))
        return list;
    if (rx.indexIn(string) != -1)
        list = rx.capturedTexts();
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
