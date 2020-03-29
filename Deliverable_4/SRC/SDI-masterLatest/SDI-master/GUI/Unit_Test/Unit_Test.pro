QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    sizegripitem.cpp\
    ../WORK!!!/Software Design and Implemenation/SDI-masterLatest/SDI-master/GUI/main.cpp \
    ../WORK!!!/Software Design and Implemenation/SDI-masterLatest/SDI-master/GUI/main.cpp \
    ../WORK!!!/Software Design and Implemenation/SDI-masterLatest/SDI-master/GUI/mainwindow.cpp \
    ../WORK!!!/Software Design and Implemenation/SDI-masterLatest/SDI-master/GUI/mainwindow.cpp \
    ../WORK!!!/Software Design and Implemenation/SDI-masterLatest/SDI-master/GUI/sizegripitem.cpp \
    ../WORK!!!/Software Design and Implemenation/SDI-masterLatest/SDI-master/GUI/sizegripitem.cpp \
    tst_test1.cpp

CONFIG += c++11




HEADERS += \
     ../WORK!!!/Software Design and Implemenation/SDI-masterLatest/SDI-master/GUI/functions.h \
     ../WORK!!!/Software Design and Implemenation/SDI-masterLatest/SDI-master/GUI/functions.h \
        ../mainwindow.h \
functions.h \
mainwindow.h\
    ../functions.h \
    sizegripitem.h

FORMS += \
        ../mainwindow.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../resources.qrc \
    resources.qrc

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

SUBDIRS += \
    ../GUI.pro

DISTFILES += \
    ../.gitignore \
    ../GUI.pro.user \
    ../GUI.pro.user.12 \
    ../GUI.pro.user.981af04.4.9-pre1 \
    ../README.md \
    ../honklhonk.jpg
