#include "colordialogbutton.h"

#include <QColorDialog>
#include <QPainter>

ColorDialogButton::ColorDialogButton(QWidget *parent) :
    QPushButton(parent)
{
//    button = new QPushButton("Select Color", this);
    QColor base(0,0,0);
    __currentColor = base;

    connect(this, SIGNAL(clicked()), this, SLOT(selectNewColor()));

    this->setText(" ");
    this->setFlat(true);

    QRect *rect = new QRect(this->rect().topLeft(),this->rect().bottomRight());
    QRegion* region = new QRegion(*rect,QRegion::Rectangle);

    this->setMask(*region);
    update();
    setButtonColor(__currentColor);
}

void ColorDialogButton::paintEvent(QPaintEvent *aPaintEvent)
{

    qreal opacity(0.675);
    int roundness(40);
    QRect widget_rect = this->rect();

    QPainter painter(this);
    painter.save();

//    painter.setRenderHint(QPainter::Antialiasing,true);
//    painter.setRenderHint(QPainter::CompositionMode_Clear);



  // clip
    QPainterPath rounded_rect;
    rounded_rect.setFillRule(Qt::FillRule::);
    painter.setBackground(__currentColor);
    rounded_rect.addRoundRect(1, 1, widget_rect.width() - 2, widget_rect.height() - 2, roundness, roundness);

    painter.setClipPath(rounded_rect);

    // get clipping region
  QRegion maskregion = painter.clipRegion();

  // mask the widget
  setMask(maskregion);
  painter.setOpacity(opacity);

  // fill path with color
//  painter.fillPath(rounded_rect,QBrush());

  // restore painter
  painter.restore();

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
