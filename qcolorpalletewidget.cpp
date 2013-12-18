#include "qcolorpalletewidget.h"
#include "ui_qcolorpalletewidget.h"

QColorPalleteWidget::QColorPalleteWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::QColorPalleteWidget)
{
    ui->setupUi(this);
    connect(ui->frontColor, SIGNAL(colorChanged(QColor)), this, SLOT(frontColorWasChanged(QColor)));
    connect(ui->backColor, SIGNAL(colorChanged(QColor)), this, SLOT(backColorWasChanged(QColor)));
}

QColorPalleteWidget::~QColorPalleteWidget()
{
    delete ui;
}

void QColorPalleteWidget::setFrontColor(QColor color) {__frontColor = color; ui->frontColor->setColor(color);}
void QColorPalleteWidget::setBackColor(QColor color) {__backColor = color; ui->backColor->setColor(color);}

void QColorPalleteWidget::frontColorWasChanged(QColor newColor)
{
    setFrontColor(newColor);
    emit frontColorChanged(newColor);
}

void QColorPalleteWidget::backColorWasChanged(QColor newColor)
{
    setBackColor(newColor);
    emit backColorChanged(newColor);
}
