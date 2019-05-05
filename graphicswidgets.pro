#-------------------------------------------------
#
# Project created by QtCreator 2019-04-30T19:00:09
#
#-------------------------------------------------

QT       += widgets

TARGET = graphicswidgets
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH    += \
    ../commons

win32 {
    CONFIG(debug, release|debug): LIBSUBDIR = debug/
    CONFIG(release, release|debug): LIBSUBDIR = release/
}

LIBS += -L../commons/$$LIBSUBDIR -lcommons

SOURCES += \
        graphicswidgets.cpp \
    colordelegate.cpp \
    crosssectionchart.cpp \
    dischargechart.cpp \
    dischargemeasurementpointitem.cpp \
    processchart.cpp \
    processpointitem.cpp \
    processxaxis.cpp \
    processxaxiswidget.cpp \
    processyaxis.cpp \
    processyaxiswidget.cpp \
    relationchart.cpp \
    relationchartperiodtableitem.cpp \
    relationcurvenotationitem.cpp \
    relationcurvenotationlinkitem.cpp \
    sedimentchart.cpp \
    stagechart.cpp \
    stagedischargerelationcurveitem.cpp \
    vchart.cpp \
    view.cpp \
    viewer.cpp

HEADERS += \
        graphicswidgets.h \
    colordelegate.h \
    crosssectionchart.h \
    dischargechart.h \
    dischargemeasurementpointitem.h \
    processchart.h \
    processpointitem.h \
    processxaxis.h \
    processxaxiswidget.h \
    processyaxis.h \
    processyaxiswidget.h \
    relationchart.h \
    relationchartperiodtableitem.h \
    relationcurvenotationitem.h \
    relationcurvenotationlinkitem.h \
    sedimentchart.h \
    stagechart.h \
    stagedischargerelationcurveitem.h \
    vchart.h \
    view.h \
    viewer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

BOOST_PATH = ../dependencies/boost

INCLUDEPATH += $$BOOST_PATH
LIBS += -L"$$BOOST_PATH/stage/lib"
