#include "colordialogbutton.h"

#include <QColorDialog>

ColorDialogButton::ColorDialogButton(QWidget *parent) :
    QPushButton(parent)
{
//    button = new QPushButton("Select Color", this);
    QColor base(0,0,0);
    __currentColor = base;

    connect(this, SIGNAL(clicked()), this, SLOT(selectNewColor()));

    this->setText(" ");
    this->setFlat(true);
    update();
    setButtonColor(__currentColor);
}

ColorDialogButton::~ColorDialogButton()
{
}

void ColorDialogButton::selectNewColor()
{
    QColor color = QColorDialog::getColor(Qt::green, this);
    if (color.isValid())
    {
//        colorLabel->setText(color.name());
//        colorLabel->setPalette(QPalette(color));
//        colorLabel->setAutoFillBackground(true);

        setButtonColor(color);
    }
    __currentColor = color;
    emit colorChanged(color);
}

void ColorDialogButton::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void ColorDialogButton::setButtonColor(QColor color)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Active, QPalette::Button,color);
    palette.setColor(QPalette::Inactive, QPalette::Button, color);



    this->setPalette(palette);
    this->setAutoFillBackground( true );
}
