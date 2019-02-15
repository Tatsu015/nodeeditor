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
    app/controller/builder \
    app/controller/command \
    app/controller/editor \
    app/controller/factory \
    app/controller/publisher \
    app/controller/tool \
    app/model/figure/connection \
    app/model/figure/node \
    app/model/figure/port \
    app/model/figure/guideline \
    app/model/scene \
    app/model/observer \
    app/model/project \
    app/util \
    app/view/widget \
    app/view/window \
    app/extend \
    app/view/menu \
    plugin/core \
    plugin/circuitcalculate \
    plugin/circuitcalculate/action \
    plugin/circuitcalculate/widget \
    plugin/core \

HEADERS += \
    app/controller/builder/Builder.h \
    app/controller/command/ConnectionAddCommand.h \
    app/controller/command/NodeAddCommand.h \
    app/controller/command/NodeRemoveCommand.h \
    app/controller/editor/Editor.h \
    app/controller/factory/ConnectionFactory.h \
    app/controller/factory/NodeFactory.h \
    app/controller/publisher/NamePublisher.h \
    app/controller/tool/AbstractTool.h \
    app/controller/tool/ConnectionCreateTool.h \
    app/controller/tool/NodeEditTool.h \
    app/extend/AbstractPlugin.h \
    app/extend/PluginLoader.h \
    app/model/figure/connection/Connection.h \
    app/model/figure/connection/Connector.h \
    app/model/figure/guideline/GuideLine.h \
    app/model/figure/node/AbstractNode.h \
    app/model/figure/node/AndNode.h \
    app/model/figure/node/InNode.h \
    app/model/figure/node/OrNode.h \
    app/model/figure/node/OutNode.h \
    app/model/figure/port/Port.h \
    app/model/project/Project.h \
    app/model/scene/Scene.h \
    app/util/Common.h \
    app/util/Define.h \
    app/view/graphicsview/GraphicsView.h \
    app/view/menu/MenuManager.h \
    app/view/widget/NodeToolBar.h \
    app/view/window/MainWindow.h \
    plugin/circuitcalculate/action/AnalyzeCircuitAction.h \
    plugin/circuitcalculate/widget/ErrorListWidget.h \
    plugin/core/NewPlugin.h \
    plugin/core/OpenPlugin.h \
    plugin/core/SavePlugin.h \
    app/controller/command/NodeMoveCommand.h \
    app/model/figure/connection/TmpConnection.h \
    plugin/circuitcalculate/CircuitCalculatePlugin.h \
    app/model/observer/SceneObserver.h \
    plugin/circuitcalculate/widget/IOTableWidget.h \
    plugin/core/QuitPlugin.h \
    plugin/circuitcalculate/DataBase.h \
    plugin/circuitcalculate/widget/DataSetComboBox.h \
    app/controller/factory/PortFactory.h

SOURCES += \
    app/controller/builder/Builder.cpp \
    app/controller/command/ConnectionAddCommand.cpp \
    app/controller/command/NodeAddCommand.cpp \
    app/controller/command/NodeRemoveCommand.cpp \
    app/controller/editor/Editor.cpp \
    app/controller/factory/ConnectionFactory.cpp \
    app/controller/factory/NodeFactory.cpp \
    app/controller/publisher/NamePublisher.cpp \
    app/controller/tool/AbstractTool.cpp \
    app/controller/tool/ConnectionCreateTool.cpp \
    app/controller/tool/NodeEditTool.cpp \
    app/extend/AbstractPlugin.cpp \
    app/extend/PluginLoader.cpp \
    app/model/figure/connection/Connection.cpp \
    app/model/figure/connection/Connector.cpp \
    app/model/figure/guideline/GuideLine.cpp \
    app/model/figure/node/AbstractNode.cpp \
    app/model/figure/node/AndNode.cpp \
    app/model/figure/node/InNode.cpp \
    app/model/figure/node/OrNode.cpp \
    app/model/figure/node/OutNode.cpp \
    app/model/figure/port/Port.cpp \
    app/model/project/Project.cpp \
    app/model/scene/Scene.cpp \
    app/util/Common.cpp \
    app/view/graphicsview/GraphicsView.cpp \
    app/view/menu/MenuManager.cpp \
    app/view/widget/NodeToolBar.cpp \
    app/view/window/MainWindow.cpp \
    app/main.cpp \
    plugin/circuitcalculate/action/AnalyzeCircuitAction.cpp \
    plugin/circuitcalculate/widget/ErrorListWidget.cpp \
    plugin/core/NewPlugin.cpp \
    plugin/core/OpenPlugin.cpp \
    plugin/core/SavePlugin.cpp \
    app/controller/command/NodeMoveCommand.cpp \
    app/model/figure/connection/TmpConnection.cpp \
    plugin/circuitcalculate/CircuitCalculatePlugin.cpp \
    app/model/observer/SceneObserver.cpp \
    plugin/circuitcalculate/widget/IOTableWidget.cpp \
    plugin/core/QuitPlugin.cpp \
    plugin/circuitcalculate/DataBase.cpp \
    plugin/circuitcalculate/widget/DataSetComboBox.cpp \
    app/controller/factory/PortFactory.cpp

FORMS += \
    app/view/window/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
