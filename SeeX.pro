#-------------------------------------------------
#
# Project created by QtCreator 2017-09-09T11:17:38
#
#-------------------------------------------------

QT       += core gui widgets svg

TARGET = SeeX
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
        application.cpp \
        fileprovider.cpp \
        frameprovider.cpp \
        imagelabel.cpp \
        mainwindow.cpp \
        statuslabel.cpp

HEADERS += \
        application.h \
        fileprovider.h \
        frameprovider.h \
        imagelabel.h \
        mainwindow.h \
        statuslabel.h

FORMS += \
        mainwindow.ui

RESOURCES += \
        images.qrc

ICON = macos/SeeX.icns
QMAKE_INFO_PLIST = macos/SeeX.plist
