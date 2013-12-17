#include "svgparser.h"

SVGParser::SVGParser()
{
}

bool SVGParser::checkRegExp(QRegExp rx)
{
    return (rx.isValid() && !rx.isEmpty() && !rx.exactMatch(""));
}
