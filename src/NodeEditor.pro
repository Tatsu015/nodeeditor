#-------------------------------------------------
#
# Project created by QtCreator 2018-09-20T23:30:12
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = NodeEditor
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

CONFIG += c++11

INCLUDEPATH += \
    controller/builder \
    controller/editor \
    controller/extend \
    controller/factory \
    controller/publisher \
    controller/tool \
    model/connection \
    model/node \
    model/scene \
    model/port \
    model/project \
    util \
    view/widget \
    view/window

HEADERS += \
    controller/editor/Editor.h \
    controller/extend/AbstractAction.h \
    controller/tool/Tool.h \
    model/connection/Connection.h \
    model/connection/Connector.h \
    model/node/HiddenNode.h \
    model/node/InNode.h \
    model/node/OutNode.h \
    model/port/Port.h \
    model/scene/Scene.h \
    util/Common.h \
    view/widget/ErrorListWidget.h \
    view/window/MainWindow.h \
    model/project/Project.h \
    controller/factory/NodeFactory.h \
    model/node/AbstractNode.h \
    util/Define.h \
    controller/publisher/NamePublisher.h \
    controller/extend/OpenAction.h \
    controller/extend/SaveAction.h \
    controller/extend/AnalyzeCircuitAction.h \
    controller/factory/ConnectionFactory.h \
    controller/builder/Builder.h

SOURCES += \
    controller/editor/Editor.cpp \
    controller/extend/AbstractAction.cpp \
    controller/tool/Tool.cpp \
    model/connection/Connection.cpp \
    model/connection/Connector.cpp \
    model/node/HiddenNode.cpp \
    model/node/InNode.cpp \
    model/node/OutNode.cpp \
    model/port/Port.cpp \
    model/scene/Scene.cpp \
    util/Common.cpp \
    view/widget/ErrorListWidget.cpp \
    view/window/MainWindow.cpp \
    main.cpp \
    model/project/Project.cpp \
    controller/factory/NodeFactory.cpp \
    model/node/AbstractNode.cpp \
    controller/publisher/NamePublisher.cpp \
    controller/extend/OpenAction.cpp \
    controller/extend/SaveAction.cpp \
    controller/extend/AnalyzeCircuitAction.cpp \
    controller/factory/ConnectionFactory.cpp \
    controller/builder/Builder.cpp

FORMS += \
    view/window/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
