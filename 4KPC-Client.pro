#-------------------------------------------------
#
# Project created by QtCreator 2019-08-19T11:24:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 4KPC-Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    CustomWidget/widget.cpp \
    CustomWidget/customtoolbutton.cpp \
    CustomWidget/leftmenubar.cpp \
    CustomWidget/stackwidgetone.cpp \
    CustomWidget/mystackedwidget.cpp \
    CustomWidget/stackwidgetprinting.cpp \
    CustomControl/cycleprocess.cpp \
    CustomControl/mytablewidget.cpp \
    CustomControl/nofocusdelegate.cpp \
    CustomWidget/stackwidgetmatrial.cpp \
    CustomControl/rollingcontrol.cpp \
    CustomWidget/stackwidgetsetting.cpp

HEADERS += \
    CustomWidget/widget.h \
    CustomWidget/customtoolbutton.h \
    CustomWidget/leftmenubar.h \
    CustomWidget/stackwidgetone.h \
    CustomWidget/mystackedwidget.h \
    CustomWidget/stackwidgetprinting.h \
    CustomControl/cycleprocess.h \
    CustomControl/mytablewidget.h \
    CustomControl/nofocusdelegate.h \
    myglobal.h \
    CustomWidget/stackwidgetmatrial.h \
    CustomControl/rollingcontrol.h \
    CustomWidget/stackwidgetsetting.h

FORMS += \
    CustomWidget/widget.ui \
    CustomWidget/leftmenubar.ui \
    CustomWidget/stackwidgetone.ui \
    CustomWidget/stackwidgetprinting.ui

RESOURCES += \
    Resource/res.qrc

DISTFILES +=
