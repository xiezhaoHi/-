#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T14:32:38
#
#-------------------------------------------------

QT       += core gui charts network
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = data_collection_designer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dataexchange.cpp \
    custom.cpp \
    mylabel.cpp \
    mylabel_add.cpp \
    CCycleBuffer.cpp \
    connectionpool.cpp \
    mydatabase.cpp

HEADERS  += mainwindow.h \
    ../build-data_collection_designer-Desktop_Qt_5_8_0_MinGW_32bit-Debug/ui_mainwindow.h \
    dataexchange.h \
    custom.h \
    mylabel.h \
    mylabel_add.h \
    ../build-data_collection_designer-Desktop_Qt_5_8_0_MinGW_32bit-Debug/ui_custom.h \
    CCycleBuffer.h \
    enum.h \
    connectionpool.h \
    mydatabase.h

FORMS    += mainwindow.ui \
    custom.ui

RESOURCES += \
    resource.qrc
