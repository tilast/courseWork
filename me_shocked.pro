#-------------------------------------------------
#
# Project created by QtCreator 2013-12-08T21:19:37
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++11
QT       += core gui
QT       += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = me_shocked
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    base.cpp \
    figure.cpp \
    shape.cpp \
    rectangle.cpp \
    qtrectangle.cpp \
    canvaswidget.cpp \
    parallelogram.cpp \
    qtparallelogram.cpp \
    qtrhombus.cpp \
    zigzag.cpp \
    qtzigzag.cpp \
    svgstyleparse.cpp \
    svgparser.cpp \
    svgfigureparser.cpp \
    arrow.cpp \
    qtarrow.cpp

HEADERS  += mainwindow.h \
    base.h \
    figure.h \
    shape.h \
    rectangle.h \
    qtshape.h \
    qtrectangle.h \
    canvaswidget.h \
    parallelogram.h \
    qtparallelogram.h \
    qtrhombus.h \
    zigzag.h \
    qtzigzag.h \
    svgstyleparse.h \
    svgparser.h \
    svgfigureparser.h \
    arrow.h \
    qtarrow.h

FORMS    += mainwindow.ui
