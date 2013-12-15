#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <iostream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), canvas(NULL)
{
    ui->setupUi(this);
    canvas = this->findChild<CanvasWidget*>("mainCanvas");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
      {
        case Qt::Key_Return:
        case Qt::Key_Enter:
          qDebug() << "Enter";
          break;
        case Qt::Key_Escape:
          qDebug() << "Escape";
          break;
        case Qt::Key_Insert:
          qDebug() << "Insert";
          break;
        case Qt::Key_Delete:
        case Qt::Key_Backspace: {

///////////////////////////////////////////////////////////////////
//                                                               //
//   Press Delete button. We you this event to delete selected   //
//   object, for example.                                        //
//                                                               //
///////////////////////////////////////////////////////////////////

        qDebug() <<"------------------ (deleting shape)";
        deleteSelected();
        qDebug() <<"------------------";

        break;
    }

          default:
          qDebug() << "other" << event->key();
          break;
      }
}
void MainWindow::deleteSelected()
{
    std::vector< QtShape2D* > *shapes = &canvas->shapes;
    QtShape2D *selectedShape = canvas->selected;

    qDebug() <<"Selected shape: "<<selectedShape;

    std::vector< QtShape2D* >::iterator itemItr = std::find(shapes->begin(), shapes->end(), selectedShape); //Searching

    if (itemItr != shapes->end()) {
        shapes->erase(itemItr);
        update();
        qDebug() <<"Item found";

    } else {

        qDebug() <<"Item not found";

    }
}
