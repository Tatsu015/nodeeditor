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
QMAKE_CXX = ccache $$QMAKE_CXX

INCLUDEPATH += \
    core/controller/builder \
    core/controller/command \
    core/controller/editor \
    core/controller/factory \
    core/controller/publisher \
    core/controller/tool \
    core/controller/pluginloader \
    core/model/figure/connection \
    core/model/figure/node \
    core/model/figure/port \
    core/model/figure/guideline \
    core/model/scene \
    core/model/observer \
    core/model/project \
    core/util \
    core/view/widget \
    core/view/window \
    core/extend \
    core/view/menu \
    core/extend \
    application \
    application/controller \
    application/extend \
    application/model \
    application/view/widget \

HEADERS += \
    application/controller/CircuitCalculateExecutor.h \
    application/extend/CircuitCalculatePlugin.h \
    application/model/DataBase.h \
    application/view/widget/DataSetComboBox.h \
    application/view/widget/DebugControlWidget.h \
    application/view/widget/ErrorListWidget.h \
    application/view/widget/IOTableWidget.h \
    core/controller/builder/Builder.h \
    core/controller/command/ConnectToConnectorCommand.h \
    core/controller/command/ConnectToPortCommand.h \
    core/controller/command/NodeAddCommand.h \
    core/controller/command/NodeMoveCommand.h \
    core/controller/command/NodeRemoveCommand.h \
    core/controller/editor/Editor.h \
    core/controller/factory/ConnectionFactory.h \
    core/controller/factory/ConnectorFactory.h \
    core/controller/factory/NodeFactory.h \
    core/controller/factory/PortFactory.h \
    core/controller/pluginloader/PluginLoader.h \
    core/controller/publisher/NamePublisher.h \
    core/controller/tool/AbstractTool.h \
    core/controller/tool/ConnectionCreateTool.h \
    core/controller/tool/NodeEditTool.h \
    core/extend/AbstractPlugin.h \
    core/extend/NewPlugin.h \
    core/extend/OpenPlugin.h \
    core/extend/QuitPlugin.h \
    core/extend/SavePlugin.h \
    core/model/figure/connection/Connection.h \
    core/model/figure/connection/Connector.h \
    core/model/figure/connection/TmpConnection.h \
    core/model/figure/guideline/GuideLine.h \
    core/model/figure/node/AbstractNode.h \
    core/model/figure/node/AndNode.h \
    core/model/figure/node/InNode.h \
    core/model/figure/node/OrNode.h \
    core/model/figure/node/OutNode.h \
    core/model/figure/port/Port.h \
    core/model/observer/SceneObserver.h \
    core/model/project/Project.h \
    core/model/scene/Scene.h \
    core/util/Common.h \
    core/util/Define.h \
    core/view/graphicsview/GraphicsView.h \
    core/view/menu/MenuManager.h \
    core/view/widget/NodeToolBar.h \
    core/view/window/MainWindow.h


SOURCES += \
    application/controller/CircuitCalculateExecutor.cpp \
    application/extend/CircuitCalculatePlugin.cpp \
    application/model/DataBase.cpp \
    application/view/widget/DataSetComboBox.cpp \
    application/view/widget/DebugControlWidget.cpp \
    application/view/widget/ErrorListWidget.cpp \
    application/view/widget/IOTableWidget.cpp \
    application/main.cpp \
    core/controller/builder/Builder.cpp \
    core/controller/command/ConnectToConnectorCommand.cpp \
    core/controller/command/ConnectToPortCommand.cpp \
    core/controller/command/NodeAddCommand.cpp \
    core/controller/command/NodeMoveCommand.cpp \
    core/controller/command/NodeRemoveCommand.cpp \
    core/controller/editor/Editor.cpp \
    core/controller/factory/ConnectionFactory.cpp \
    core/controller/factory/ConnectorFactory.cpp \
    core/controller/factory/NodeFactory.cpp \
    core/controller/factory/PortFactory.cpp \
    core/controller/pluginloader/PluginLoader.cpp \
    core/controller/publisher/NamePublisher.cpp \
    core/controller/tool/AbstractTool.cpp \
    core/controller/tool/ConnectionCreateTool.cpp \
    core/controller/tool/NodeEditTool.cpp \
    core/extend/AbstractPlugin.cpp \
    core/extend/NewPlugin.cpp \
    core/extend/OpenPlugin.cpp \
    core/extend/QuitPlugin.cpp \
    core/extend/SavePlugin.cpp \
    core/model/figure/connection/Connection.cpp \
    core/model/figure/connection/Connector.cpp \
    core/model/figure/connection/TmpConnection.cpp \
    core/model/figure/guideline/GuideLine.cpp \
    core/model/figure/node/AbstractNode.cpp \
    core/model/figure/node/AndNode.cpp \
    core/model/figure/node/InNode.cpp \
    core/model/figure/node/OrNode.cpp \
    core/model/figure/node/OutNode.cpp \
    core/model/figure/port/Port.cpp \
    core/model/observer/SceneObserver.cpp \
    core/model/project/Project.cpp \
    core/model/scene/Scene.cpp \
    core/util/Common.cpp \
    core/view/graphicsview/GraphicsView.cpp \
    core/view/menu/MenuManager.cpp \
    core/view/widget/NodeToolBar.cpp \
    core/view/window/MainWindow.cpp \


FORMS += \
    application/view/widget/DebugControlWidget.ui \
    core/view/window/MainWindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
