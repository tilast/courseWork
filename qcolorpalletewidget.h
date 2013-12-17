#ifndef QCOLORPALLETEWIDGET_H
#define QCOLORPALLETEWIDGET_H

#include <QFrame>
#include <colordialogbutton.h>

namespace Ui {
class QColorPalleteWidget;
}

class QColorPalleteWidget : public QFrame
{
    Q_OBJECT

public:
    explicit QColorPalleteWidget(QWidget *parent = 0);
    ~QColorPalleteWidget();

    QColor getFrontColor() {return __frontColor;}
    QColor getBackColor() {return __backColor;}

signals:
    void frontColorChanged(QColor newFrontColor);
    void backColorChanged(QColor newBackColor);

public slots:
    void frontColorWasChanged(QColor newColor);
    void backColorWasChanged(QColor newColor);

private:
    Ui::QColorPalleteWidget *ui;

    QColor __frontColor;
    QColor __backColor;
};

#endif // QCOLORPALLETEWIDGET_H
