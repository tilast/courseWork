#include "svgstyleparse.h"

SVGStyleParse::SVGStyleParse(const QString &string)
{
    setParseString(string);
}

QStringList SVGStyleParse::getFillColor()
{
    QString str = "Я написал 1 число";
    QStringList result;

//    QRegExp rx("((\\d)+)");
        QRegExp rx("fill:rgb\\(\[\\s\]*(\[\\S\]+),\[\\s\]*(\[\\S\]+),\[\\s\]*(\[\\S\]+)\[\\s\]*\\)");

    if(!checkRegExp(rx))
        return result;

    if (rx.indexIn(getParseString()) != -1)
        result = rx.capturedTexts();

    return result;
}


