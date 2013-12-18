#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QLineEdit>

#include <QtXml/qdom.h>

#include <QRegExp>

#include <QColorDialog>

#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

#include <svgstyleparse.h>
#include <svgfigureparser.h>

#include "colordialogbutton.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), canvas(NULL)
{
    ui->setupUi(this);
    canvas = ui->mainCanvas;

    connect(canvas,SIGNAL(shapeSelected(int)),this,SLOT(selectShape(int)));

    QColor frontColor(canvas->currentBackColor.red * 255.0,canvas->currentBackColor.green* 255.0,canvas->currentBackColor.blue* 255.0);
    QColor backColor(canvas->currentLineColor.red * 255.0,canvas->currentLineColor.green* 255.0,canvas->currentLineColor.blue* 255.0);
    qDebug() <<frontColor;
    ui->colorPanel->setFrontColor(frontColor);
    ui->colorPanel->setBackColor(backColor);
    createActions();
    createMenus();

    setCurrentFile("Untitled");
    setUnifiedTitleAndToolBarOnMac(true);


}

bool MainWindow::eventFilter( QObject * o, QEvent * e ) {
    if ( e->type() == QEvent::Wheel &&
         qobject_cast<QAbstractSpinBox*>( o ) )
    {
        e->ignore();
        return true;
    }
    qDebug() <<"event filter";
    return QWidget::eventFilter( o, e );
}

void MainWindow::shapeDefault()
{
    ui->arrowsTipCoefficient->setEnabled(false);
    ui->zigzagPoints->setEnabled(false);
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
    qDebug() <<"Key pressed";
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
        canvas->update();
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
        if (itemItr != shapes->end())
            shapes->erase(itemItr);
    }
//    update();
    canvas->update();
}

void MainWindow::setTextToClipboard(const QString &text)
{
    qDebug() <<"Save to clipboard: "<<text;
    QApplication::clipboard()->setText(text);
}

const QString MainWindow::getTextToClipboard()
{
    return QApplication::clipboard()->text();
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
    shapesContainer result;
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return result;
    }

    QString content = file->readAll();
    if (!content.isEmpty()) {
        result = parseXMLTextForSVG(content);
    }

    return result;
}

shapesContainer MainWindow::parseXMLTextForSVG(const QString &svgText)
{
    shapesContainer newContainer;
    if (svgText.isEmpty())
        return newContainer;

    QDomDocument doc;
    doc.setContent(svgText);
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
      while( !n.isNull() ) {
          QDomElement e = n.toElement(); // try to convert the node to an element.
          if( !e.isNull() ) { // the node was really an element.

              QtShape2D *shape = SVGFigureParser::parseFigure(e);
              if (shape != NULL)
                  newContainer.push_back(shape);
          }
          n = n.nextSibling();
      }

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
    connect(ui->takeRhombus, SIGNAL(clicked(bool)), this, SLOT(selectRhombus()));
    connect(ui->takeZigzag, SIGNAL(clicked(bool)), this, SLOT(selectZigzag()));
    connect(ui->takeArrow, SIGNAL(clicked(bool)), this, SLOT(selectArrow()));

    connect(ui->colorPanel, SIGNAL(frontColorChanged(QColor)),this,SLOT(selectFillColor(QColor)));
    connect(ui->colorPanel, SIGNAL(backColorChanged(QColor)),this,SLOT(selectLineColor(QColor)));


    connect(ui->zigzagPoints, SIGNAL(valueChanged(int)), this, SLOT(setZigzagPointAmount(int)));
    connect(ui->arrowsTipCoefficient, SIGNAL(valueChanged(double)), this, SLOT(setArrowsTipCoeficient(double)));

    connect(ui->reflect, SIGNAL(clicked(bool)), this, SLOT(reflect()));
}

void MainWindow::reflect() {
    canvas->reflect();
}

void MainWindow::setArrowsTipCoeficient(double coef)
{
    canvas->setArrowsTipCoefficient(coef);
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
    canvas->update();
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
    return save();
}

bool MainWindow::exportSVG()
{
    canvas->setModified(false);
    return saveFileByText(curFileName, svgImageCode(&canvas->shapes));

}
void MainWindow::print() { qDebug() <<"print file"; }

void MainWindow::undo() { qDebug() <<"undo"; }
void MainWindow::redo() { qDebug() <<"redo"; }

void MainWindow::cut()
{
    qDebug() <<"cut";
    copy();
    deleteSelected();
}
void MainWindow::copy()
{
    qDebug() <<"copy";
    shapesContainer output(canvas->selectedShapes.begin(), canvas->selectedShapes.end());
    QString svgToClipboard = svgImageCode(&output);
    setTextToClipboard(svgToClipboard);
}
void MainWindow::paste()
{
    qDebug() <<"paste";
    QString clipText = getTextToClipboard();
    shapesContainer newShapes = parseXMLTextForSVG(clipText);
    canvas->shapes.insert(canvas->shapes.end(),newShapes.begin(), newShapes.end());

    canvas->update();


}
void MainWindow::selectAll()
{
    canvas->selectAll();
}

void MainWindow::deleteAction()
{
    deleteSelected();
}

void MainWindow::about()  { qDebug() <<"about"; }

void MainWindow::selectShape(int type)
{

    qDebug() <<"selected "<<type;
    switch(type) {
    case 1:
        selectRectangle();
        break;
    case 2:
        selectParallelogram();
        break;
    case 3:
        selectRhombus();
        break;
    case 4:
        selectZigzag();
        break;
    case 5:
        selectArrow();
        break;
    }
}


void MainWindow::selectFillColor(QColor newFillColor)
{
    canvas->changeBackColor(newFillColor);
}

void MainWindow::selectLineColor(QColor newLineColor)
{
    canvas->changeLineColor(newLineColor);

}


void MainWindow::selectRectangle() {
    shapeDefault();
    canvas->changeType(1);
    ui->takeRectangle->setChecked(true);
    instrument = FIGURE;
}
void MainWindow::selectParallelogram() {
    shapeDefault();
    canvas->changeType(2);
    ui->takeParallelogram->setChecked(true);
    instrument = FIGURE;
}
void MainWindow::selectRhombus() {
    shapeDefault();
    canvas->changeType(3);
    ui->takeRhombus->setChecked(true);
    instrument = FIGURE;
}

void MainWindow::selectZigzag() {
    shapeDefault();
    canvas->changeType(4);
    ui->takeZigzag->setChecked(true);
    instrument = FIGURE;
    ui->zigzagPoints->setEnabled(true);
}

void MainWindow::selectArrow() {
    shapeDefault();
    canvas->changeType(5);
    ui->takeArrow->setChecked(true);
    instrument = FIGURE;
    ui->arrowsTipCoefficient->setEnabled(true);
}

void MainWindow::setZigzagPointAmount(int amount) {
    canvas->setZigzagPointAmount(amount);
}
