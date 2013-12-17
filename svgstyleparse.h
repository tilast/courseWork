#ifndef SVGSTYLEPARSE_H
#define SVGSTYLEPARSE_H

#include "svgparser.h"

class SVGStyleParse: public SVGParser
{
public:
    SVGStyleParse();
    SVGStyleParse(const QString &string);
    void setParseString(const QString &string) {__parseString = string;}
    QString getParseString() {return __parseString;}

    QStringList getFillColor();

private:
    QString __parseString;

};

#endif // SVGSTYLEPARSE_H
