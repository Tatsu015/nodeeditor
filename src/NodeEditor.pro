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
    controller/action \
    controller/factory \
    controller/publisher \
    controller/tool \
    model/figure/connection \
    model/figure/node \
    model/figure/port \
    model/figure/guideline \
    model/scene \
    model/project \
    util \
    view/widget \
    view/window

HEADERS += \
    controller/action/AbstractAction.h \
    controller/action/AnalyzeCircuitAction.h \
    controller/action/OpenAction.h \
    controller/action/SaveAction.h \
    controller/builder/Builder.h \
    controller/editor/Editor.h \
    controller/factory/ConnectionFactory.h \
    controller/factory/NodeFactory.h \
    controller/publisher/NamePublisher.h \
    controller/tool/AbstractTool.h \
    controller/tool/ConnectionCreateTool.h \
    controller/tool/NodeEditTool.h \
    controller/tool/Tool.h \
    model/figure/connection/Connection.h \
    model/figure/connection/Connector.h \
    model/figure/node/AbstractNode.h \
    model/figure/node/AndNode.h \
    model/figure/node/InNode.h \
    model/figure/node/OrNode.h \
    model/figure/node/OutNode.h \
    model/figure/port/Port.h \
    model/project/Project.h \
    model/scene/Scene.h \
    util/Common.h \
    util/Define.h \
    view/graphicsview/GraphicsView.h \
    view/widget/ErrorListWidget.h \
    view/widget/NodeToolBar.h \
    view/window/MainWindow.h \
    model/figure/guideline/GuideLine.h

SOURCES += \
    controller/action/AbstractAction.cpp \
    controller/action/AnalyzeCircuitAction.cpp \
    controller/action/OpenAction.cpp \
    controller/action/SaveAction.cpp \
    controller/builder/Builder.cpp \
    controller/editor/Editor.cpp \
    controller/factory/ConnectionFactory.cpp \
    controller/factory/NodeFactory.cpp \
    controller/publisher/NamePublisher.cpp \
    controller/tool/AbstractTool.cpp \
    controller/tool/ConnectionCreateTool.cpp \
    controller/tool/NodeEditTool.cpp \
    controller/tool/Tool.cpp \
    model/figure/connection/Connection.cpp \
    model/figure/connection/Connector.cpp \
    model/figure/node/AbstractNode.cpp \
    model/figure/node/AndNode.cpp \
    model/figure/node/InNode.cpp \
    model/figure/node/OrNode.cpp \
    model/figure/node/OutNode.cpp \
    model/figure/port/Port.cpp \
    model/project/Project.cpp \
    model/scene/Scene.cpp \
    util/Common.cpp \
    view/graphicsview/GraphicsView.cpp \
    view/widget/ErrorListWidget.cpp \
    view/widget/NodeToolBar.cpp \
    view/window/MainWindow.cpp \
    main.cpp \
    model/figure/guideline/GuideLine.cpp

FORMS += \
    view/window/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

