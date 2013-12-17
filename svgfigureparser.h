#ifndef SVGFIGUREPARSER_H
#define SVGFIGUREPARSER_H

#include "svgparser.h"

class SVGFigureParser: public SVGParser
{
public:
    SVGFigureParser();
    void setContent(const QString &string) {__content = string;}
    QString getContent() {return __content;}

private:
    QString __content;
};

#endif // SVGFIGUREPARSER_H
