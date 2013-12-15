#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"

#include <QAction>

#include <QDebug>
#include <QKeyEvent>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void keyPressEvent(QKeyEvent* event);
    void deleteSelected();

private slots:

    void newFile();
    void open();
    void close();

    bool save();
    bool saveAs();

    void print();

    void undo();
    void redo();

    void cut();
    void copy();
    void paste();

    void selectAll();

    void deleteAction();

    void about();

private:
    Ui::MainWindow *ui;
    CanvasWidget *canvas;

    QString curFile;

    void createMenus();
    void createActions();
    void loadFile(const QString &fileName);

    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *closeAct;
    QAction *printAct;

    QAction *undoAct;
    QAction *redoAct;

    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *deleteAct;
    QAction *selectAllAct;

    QAction *aboutAct;

};

#endif // MAINWINDOW_H
