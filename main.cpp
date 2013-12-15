#include "mainwindow.h"
//#include "mainwindow_GraphicsScene.h"
#include <QApplication>

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    MainWindow w;
    w.show();

    return a.exec();
}
