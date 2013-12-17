#ifndef SVGFIGUREPARSER_H
#define SVGFIGUREPARSER_H

#include "svgparser.h"
#include "svgstyleparse.h"

#include "QtShapeHeaders.h"

#include <QtXml/qdom.h>

class SVGFigureParser: public SVGStyleParse
{
public:
    SVGFigureParser() {};
    void setContent(const QString &string) {__content = string;}
    QString getContent() {return __content;}

    static QStringList parsePoints(const QString &string);
    static QtShape2D* parseFigure(const QDomElement &e) {
        QtShape2D *shape  = NULL;
        //Parse form
        if (e.tagName() == "rect")
            shape = parseRect(e);
        if (e.tagName() == "polygon")
            shape = parsePolygon(e);

        if (shape == NULL)
            return NULL;

        //Style parsing
        float red = 0, green = 0, blue = 0;
        if (!e.attribute("style").isEmpty()) {
             QString style  = e.attribute("style");
             SVGStyleParse styleParse(style); //Parse style Css
             if (!style.isEmpty()) {
                //Fill color
                 QStringList fillColorStr = styleParse.getFillColor();
                 if (!fillColorStr.isEmpty()) {
                     red = fillColorStr[1].toFloat() / 255.0;
                     green = fillColorStr[2].toFloat() / 255.0;
                     blue = fillColorStr[3].toFloat() / 255.0;
                 }

                 //Line color;
            }
        }

        Color fillColor(red, green, blue);

        if (shape != NULL) {
            shape->getStyle().setStyle(Color(0,0,0), fillColor);
        }

        return shape;
    }

    static QtRectangle* parseRect(const QDomElement &element);

    static QtShape2D *parsePolygon(const QDomElement &element);
    static QtParallelogram *parseParallelogram(const QDomElement &element);
    static QtRhombus *parseRhombus(const QDomElement &element);

private:
    QString __content;
};

#endif // SVGFIGUREPARSER_H
