#include "svgstyleparse.h"

SVGStyleParse::SVGStyleParse(const QString &string)
{
    setParseString(string);
}

QStringList SVGStyleParse::getFillColor()
{
    QStringList result;

    QRegExp rx("fill:rgb\\(\[\\s\]*(\[\\d\\.\]+),\[\\s\]*(\[\\d\\.\]+),\[\\s\]*(\[\\d\\.\]+)\[\\s\]*\\)");

    if(!checkRegExp(rx))
        return result;

    if (rx.indexIn(getParseString()) != -1)
        result = rx.capturedTexts();

    return result;
}


