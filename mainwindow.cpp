#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QXmlStreamReader>

#include <vector>
#include <iostream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), canvas(NULL)
{
    ui->setupUi(this);
    canvas = this->findChild<CanvasWidget*>("mainCanvas");

    createActions();
    createMenus();

    setCurrentFile("Untitled");
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

void MainWindow::setCurrentFile(const QString &filename)
{
    curFileName = filename;
    this->setWindowTitle(curFileName);

}

///////////////////////////////////////////////////////////////////
//                                                               //
//   SVG CODING & PARSING                                        //
//                                                               //
///////////////////////////////////////////////////////////////////

const QString MainWindow::svgImageCode(shapesContainer *shapes)
{
    QString elements;
    for(shapesContainer::const_iterator it = shapes->begin(); it != shapes->end(); it++) {
        elements += (*it)->svgElementCode();
    }
    QString svgCode = QString(
                "<svg width=\"%2\" height=\"%3\">%1</svg>"
                ).arg(elements).arg(canvas->geometry().width())
            .arg(canvas->geometry().height());

    return svgCode;
}

shapesContainer MainWindow::parseXMLFileForSVG(const QString &filename)
{
    QFile* file = new QFile(filename);
    shapesContainer newContainer;

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return newContainer;
    }


    QXmlStreamReader xml(file);

    while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartDocument)
                continue;
            if (token == QXmlStreamReader::StartElement)
            {
                if (xml.name() == "svg")
                    continue;
                if (xml.name() == "rect") {
                    double height = xml.attributes().value("height").toString().toDouble();
                    double width = xml.attributes().value("width").toString().toDouble();
                    double x = xml.attributes().value("x").toString().toDouble();
                    double y = xml.attributes().value("y").toString().toDouble();
                    Point2D first(x,y);
                    Point2D second(x+width,y+height);

                    newContainer.push_back(new QtRectangle(first, second));
                }
            }
        }
    return newContainer;
}

shapesContainer MainWindow::parseXMLTextForSVG(const QString &svgText)
{
    shapesContainer newContainer;

    if (svgText.isEmpty())
        return newContainer;

//    QXmlStreamReader xml(file);

//    while (!xml.atEnd() && !xml.hasError())
//        {
//            QXmlStreamReader::TokenType token = xml.readNext();
//            if (token == QXmlStreamReader::StartDocument)
//                continue;
//            if (token == QXmlStreamReader::StartElement)
//            {
//                if (xml.name() == "svg")
//                    continue;
//                if (xml.name() == "rect") {
//                    double height = xml.attributes().value("height").toDouble();
//                    double width = xml.attributes().value("width").toDouble();
//                    double x = xml.attributes().value("x").toDouble();
//                    double y = xml.attributes().value("y").toDouble();
//                    Point2D first(x,y);
//                    Point2D second(x+width,y+height);

//                    newContainer.push_back(new QtRectangle(first, second));
//                }
//            }
//        }
    return newContainer;
}

///////////////////////////////////////////////////////////////////
//                                                               //
//   LOAD & SAVE FILE                                            //
//                                                               //
///////////////////////////////////////////////////////////////////

bool MainWindow::haveToSave() {
    if (canvas->isModified() and canvas->shapes.size() > 0) {
             QMessageBox::StandardButton ret;
             ret = QMessageBox::warning(this, tr("Application"),
                          tr("The document has been modified.\n", "Do you want to save your changes?"),
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

QString MainWindow::loadFileText(const QString &fileName)
{
    QString result;
    if (fileName.isEmpty()) return "" ;
    else {
             QFile file(fileName);
             if (!file.open(QIODevice::ReadOnly)) {
                 QMessageBox::information(this, tr("Unable to open file"),
                 file.errorString());
                 return "";
             }
             QTextStream in(&file);
             result = in.readAll();
    }
    return result;
}

QString MainWindow::loadFileNameDialog() {
    return QFileDialog::getOpenFileName(this,
                                        tr("Open SVG picture"), "",
                                        tr("SVG picture (*.svg);;All Files (*)"));
}

QString MainWindow::saveFileNameDialog() {
    return QFileDialog::getSaveFileName(
                this,
                tr("Save SVG"), "",
                tr("SVG files (*.svg);;All Files (*)")
                );
}

bool MainWindow::saveFileByText(QString fileName, QString text) {
    if (fileName.isEmpty()) {
        fileName = saveFileNameDialog();
    }
    if (fileName.isEmpty())
             return false;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return false;
        }
        QTextStream out(&file);
            out <<text;
    }

}

bool MainWindow::saveFileByData(QString fileName)
{
    if (fileName.isEmpty()) {
        fileName = saveFileNameDialog();
    }
    if (fileName.isEmpty())
             return false;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
            return false;
        }
        QDataStream out(&file);
            out.setVersion(QDataStream::Qt_5_0);
            out <<canvas->shapes.data();
    }

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
    newAct = this->findChild<QAction*>("actionNew");
    connect(newAct,SIGNAL(triggered()),this,SLOT(newFile()));
    openAct = this->findChild<QAction*>("actionOpen");
    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));

    saveAct = this->findChild<QAction*>("actionSave");
    connect(saveAct,SIGNAL(triggered()),this,SLOT(save()));
    saveAsAct = this->findChild<QAction*>("actionSaveAs");
    connect(saveAsAct,SIGNAL(triggered()),this,SLOT(saveAs()));

    exportSVGAct = this->findChild<QAction*>("actionExport_SVG");
    connect(exportSVGAct,SIGNAL(triggered()),this,SLOT(exportSVG()));

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

void MainWindow::newFile() { qDebug() <<"new file"; }
void MainWindow::open() //Open file
{
    if (haveToSave()) {
        setCurrentFile(loadFileNameDialog());
        canvas->shapes.clear();
        canvas->shapes = parseXMLFileForSVG(curFileName);
    }
    update();
}

void MainWindow::close() { //Closing file
    haveToSave();
}

bool MainWindow::save() { //Save file
    if(saveFileByText(curFileName, svgImageCode(&canvas->shapes))) {
        canvas->setModified(false);
        return true;
    }
    return false;

}
bool MainWindow::saveAs()
{
    QString newFileName = saveFileNameDialog();
    if (newFileName.isEmpty())
        return false;
    setCurrentFile(newFileName);
    save();
}

bool MainWindow::exportSVG()
{
    canvas->setModified(false);
    return saveFileByText(curFileName, svgImageCode(&canvas->shapes));

}
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
void MainWindow::selectRectangle() {
    canvas->changeType(1);
}
void MainWindow::selectParallelogram() {
    canvas->changeType(2);
}
