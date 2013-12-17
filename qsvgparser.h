#ifndef QSVGPARSER_H
#define QSVGPARSER_H

#include <qtshape.h>
#include <qtrectangle.h>
#include <QtXml/qdom.h>

class QSVGParser
{
public:
    QSVGParser();

    QString svgCodeForShape(QtShape2D *shape) {

    }
private:
    QDomNode __nodeForRectangle(QtRectangle *rectangle) {
        QDomNode rectNode;

    }
};

#endif // QSVGPARSER_H
