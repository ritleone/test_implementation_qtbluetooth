#-------------------------------------------------
#
# Project created by QtCreator 2020-01-14T10:08:02
#
#-------------------------------------------------

QT       += core gui bluetooth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetBluetooth
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    bluetoothe.cpp

HEADERS  += dialog.h \
    bluetoothe.h

FORMS    += dialog.ui \
    bluetoothe.ui
