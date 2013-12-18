#include "qimageradiobutton.h"
#include <QRadioButton>

QImageRadioButton::QImageRadioButton(QWidget *parent) :
    QWidget(parent)
{
    QRect geom = this->geometry();
    geom.setY(0);
    this->setGeometry(geom);
}

QImageRadioButton::~QImageRadioButton()
{
}
