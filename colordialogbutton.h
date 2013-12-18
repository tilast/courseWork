#ifndef COLORDIALOGBUTTON_H
#define COLORDIALOGBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QColorDialog>
#include <QLabel>
#include <QVBoxLayout>

class ColorDialogButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ColorDialogButton(QWidget *parent = 0);
    ~ColorDialogButton();
    QColor color() {return __currentColor;}
    void setColor(QColor newColor) {__currentColor = newColor;}
signals:
    void colorChanged(QColor newColor);

protected slots:
    void selectNewColor(); //Show color dialog and select new color after click

private:
    QColor __currentColor;

    QPushButton *button;
    QLabel *colorLabel;
    QVBoxLayout *layout;

    void clearLayout(QLayout *layout);
    void setButtonColor(QColor color);

};

#endif // COLORDIALOGBUTTON_H
