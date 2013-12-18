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
    qtarrow.cpp \
    qtshape.cpp \
    qsvgparser.cpp \
    qcolorpalletewidget.cpp \
    colordialogbutton.cpp

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
    qtarrow.h \
    QtShapeHeaders.h \
    qsvgparser.h \
    qcolorpalletewidget.h \
    colordialogbutton.h

FORMS    += mainwindow.ui \
    qcolorpalletewidget.ui \
    colordialogbutton.ui

OTHER_FILES += \
    README.md \
    me_shocked_MACOSX.pro.user \
    me_shocked_MACOSX.pro \
    me_shocked.pro.user \
    LICENSE \
    exit \
    images/icons/zigzag.psd \
    images/icons/zigzag.png \
    images/icons/romb.psd \
    images/icons/romb.png \
    images/icons/rect.psd \
    images/icons/rect.png \
    images/icons/parm.psd \
    images/icons/parm.png \
    images/icons/arrow.psd \
    images/icons/arrow.png

RESOURCES += \
    images.qrc \
    icons.qrc
