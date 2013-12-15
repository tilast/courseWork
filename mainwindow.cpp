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

void MainWindow::keyReleaseEvent(QKeyEvent * event) {
    canvas->pressedKeyCode = 0;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    canvas->pressedKeyCode = event->key();
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

/////////////////////////////////////////////////////////////////////
////                                                               //
////   Press Delete button. We you this event to delete selected   //
////   object, for example.                                        //
////                                                               //
/////////////////////////////////////////////////////////////////////

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
    shapesContainer *shapes = &canvas->shapes;
    selectedShapesContainer *selectedShapes = &canvas->selectedShapes;
    qDebug() <<"To delete: "<<selectedShapes->size();
    for(selectedShapesContainer::const_iterator it = selectedShapes->begin(); it != selectedShapes->end(); it++) {
        shapesContainer::iterator itemItr = std::find(shapes->begin(), shapes->end(), *it); //Searching
        if (itemItr != shapes->end()) {
            shapes->erase(itemItr);
            qDebug() <<"Item found";
        } else {
            qDebug() <<"Item not found";
        }
    }
                update();
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

void MainWindow::createMenus() { qDebug() <<"menu creation"; }
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

bool MainWindow::save() {
    qDebug() <<"save file";
//    return true;

    shapesContainer *shapes = &canvas->shapes;
    selectedShapesContainer *selectedShapes = &canvas->selectedShapes;
    QString elements;
    for(shapesContainer::const_iterator it = shapes->begin(); it != shapes->end(); it++) {
        elements += (*it)->svgElementCode();
    }

    QString svgCode = QString("<svg width=\"%2\" height=\"%3\">%1</svg>").arg(elements).arg(canvas->geometry().width()).arg(canvas->geometry().height());
    qDebug() <<svgCode;
    return true;
}
bool MainWindow::saveAs() { qDebug() <<"saveAs file"; return true;}

void MainWindow::print() { qDebug() <<"print file"; }

void MainWindow::undo() { qDebug() <<"undo"; }
void MainWindow::redo() { qDebug() <<"redo"; }

void MainWindow::cut() { qDebug() <<"cut"; }
void MainWindow::copy() { qDebug() <<"copy"; }
void MainWindow::paste()  { qDebug() <<"paste"; }
void MainWindow::selectAll()  {
    canvas->selectAll();
}

void MainWindow::deleteAction()  { qDebug() <<"delete"; deleteSelected(); }

void MainWindow::about()  { qDebug() <<"about"; }
