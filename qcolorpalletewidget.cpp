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

void QColorPalleteWidget::frontColorWasChanged(QColor newColor)
{
    __frontColor = newColor;
    emit frontColorChanged(newColor);
}

void QColorPalleteWidget::backColorWasChanged(QColor newColor)
{
    __backColor = newColor;
    emit backColorChanged(newColor);
}
