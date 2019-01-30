#-------------------------------------------------
#
# Project created by QtCreator 2018-04-28T13:03:41
#
#-------------------------------------------------

QT       += core gui widgets serialport

TARGET = xtQToolBox
TEMPLATE = app

INCLUDEPATH += ./examples ./widget

SOURCES += main.cpp\
        mainwindow.cpp \
    examples/analogclock.cpp \
    widget/SeiralPortWidget.cpp

HEADERS  += mainwindow.h \
    examples/analogclock.h \
    widget/SerialPortWidget.h

FORMS    += mainwindow.ui
