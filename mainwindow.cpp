#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <vector>
#include <iostream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), canvas(NULL)
{
    ui->setupUi(this);
    canvas = this->findChild<CanvasWidget*>("mainCanvas");

    createActions();
    createMenus();

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);
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


bool MainWindow::maybeSave() {
    if (canvas->isModified()) {
             QMessageBox::StandardButton ret;
             ret = QMessageBox::warning(this, tr("Application"),
                          tr("The document has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save |
                                        QMessageBox::Discard |
                                        QMessageBox::Cancel);
             if (ret == QMessageBox::Save)
                 return save();
             else if (ret == QMessageBox::Cancel)
                 return false;
         }
         return true;

}

///////////////////////////////////////////////////////////////////
//                                                               //
//   UI SLOTS                                                    //
//                                                               //
///////////////////////////////////////////////////////////////////

void MainWindow::createMenus() {
    qDebug() <<"menu creation";
    connect(ui->takeRectangle, SIGNAL(clicked(bool)), this, SLOT(selectRectangle()));
    connect(ui->takeParallelogram, SIGNAL(clicked(bool)), this, SLOT(selectParallelogram()));
}
void MainWindow::createActions()
{
    qDebug() <<"actions creation";

    newAct = this->findChild<QAction*>("actionNew");
    connect(newAct,SIGNAL(triggered()),this,SLOT(newFile()));
    openAct = this->findChild<QAction*>("actionOpen");
    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));

    saveAct = this->findChild<QAction*>("actionSave");
    connect(saveAct,SIGNAL(triggered()),this,SLOT(save()));
    saveAsAct = this->findChild<QAction*>("actionSaveAs");
    connect(saveAsAct,SIGNAL(triggered()),this,SLOT(saveAs()));

    closeAct = this->findChild<QAction*>("actionClose");
    connect(closeAct,SIGNAL(triggered()),this,SLOT(close()));
    printAct = this->findChild<QAction*>("actionPrint");
    connect(printAct,SIGNAL(triggered()),this,SLOT(print()));

    undoAct = this->findChild<QAction*>("actionUndo");
    connect(undoAct,SIGNAL(triggered()),this,SLOT(undo()));
    redoAct = this->findChild<QAction*>("actionRedo");
    connect(redoAct,SIGNAL(triggered()),this,SLOT(redo()));

    cutAct = this->findChild<QAction*>("actionCut");
    connect(cutAct,SIGNAL(triggered()),this,SLOT(cut()));
    copyAct = this->findChild<QAction*>("actionCopy");
    connect(copyAct,SIGNAL(triggered()),this,SLOT(copy()));
    pasteAct = this->findChild<QAction*>("actionPaste");
    connect(pasteAct,SIGNAL(triggered()),this,SLOT(paste()));

    deleteAct = this->findChild<QAction*>("actionDelete");
    connect(deleteAct,SIGNAL(triggered()),this,SLOT(deleteAction()));

    selectAllAct = this->findChild<QAction*>("actionSelectAll");
    connect(selectAllAct,SIGNAL(triggered()),this,SLOT(selectAll()));

}
void MainWindow::loadFile(const QString &fileName) { qDebug() <<"file loading"; }
bool MainWindow::saveFile(const QString &fileName) { qDebug() <<"file saving"; }
void MainWindow::setCurrentFile(const QString &fileName) { qDebug() <<"current file setting"; }

void MainWindow::newFile() { qDebug() <<"new file"; }
void MainWindow::open() {qDebug() <<"open file";}
void MainWindow::close() {qDebug() <<"close file";}

bool MainWindow::save() { qDebug() <<"save file";  return true;}
bool MainWindow::saveAs() { qDebug() <<"saveAs file"; return true;}

void MainWindow::print() { qDebug() <<"print file"; }

void MainWindow::undo() { qDebug() <<"undo"; }
void MainWindow::redo() { qDebug() <<"redo"; }

void MainWindow::cut() { qDebug() <<"cut"; }
void MainWindow::copy() { qDebug() <<"copy"; }
void MainWindow::paste()  { qDebug() <<"paste"; }
void MainWindow::selectAll()  { qDebug() <<"selectAll"; }

void MainWindow::deleteAction()  { deleteSelected(); }

void MainWindow::about()  { qDebug() <<"about"; }
void MainWindow::selectRectangle() {
    canvas->changeType(1);
}
void MainWindow::selectParallelogram() {
    canvas->changeType(2);
}
