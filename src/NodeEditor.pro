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
#QMAKE_CXX = ccache $$QMAKE_CXX

INCLUDEPATH += \
    core/controller/builder \
    core/controller/command \
    core/controller/editor \
    core/controller/factory \
    core/controller/publisher \
    core/controller/tool \
    core/controller/parser \
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
    core/model/sheet \
    core/view/dialog \
    core/controller/history

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
    core/controller/command/ReconnectToPortCommand.h \
    core/controller/command/NodeAddCommand.h \
    core/controller/command/PortAddCommand.h \
    core/controller/command/PortRemoveCommand.h \
    core/controller/command/NodeMoveCommand.h \
    core/controller/command/NodeRemoveCommand.h \
    core/controller/command/NodeReplaceCommand.h \
    core/controller/editor/Editor.h \
    core/controller/factory/ConnectionFactory.h \
    core/controller/factory/ConnectorFactory.h \
    core/controller/factory/NodeFactory.h \
    core/controller/factory/PortFactory.h \
    core/controller/pluginloader/PluginLoader.h \
    core/controller/tool/AbstractTool.h \
    core/controller/tool/ConnectionCreateTool.h \
    core/controller/tool/NodeEditTool.h \
    core/controller/tool/SheetJumpTool.h \
    core/extend/AbstractPlugin.h \
    core/extend/NewPlugin.h \
    core/extend/ClosePlugin.h \
    core/extend/OpenPlugin.h \
    core/extend/QuitPlugin.h \
    core/extend/SavePlugin.h \
    core/model/figure/connection/Connector.h \
    core/model/figure/guideline/GuideLine.h \
    core/model/figure/node/AbstractNode.h \
    core/model/figure/node/AndNode.h \
    core/model/figure/node/InNode.h \
    core/model/figure/node/OrNode.h \
    core/model/figure/node/OutNode.h \
    core/model/figure/node/NotNode.h \
    core/model/figure/node/ClockNode.h \
    core/model/figure/node/FlipFlopNode.h \
    core/model/figure/node/FunctionBlockNode.h \
    core/model/figure/port/Port.h \
    core/model/observer/SceneObserver.h \
    core/model/project/Project.h \
    core/model/scene/Scene.h \
    core/util/Common.h \
    core/util/SystemConfig.h \
    core/util/Define.h \
    core/view/graphicsview/GraphicsView.h \
    core/view/menu/MenuManager.h \
    core/view/menu/ContextMenuManager.h \
    core/view/window/MainWindow.h \
    core/extend/ShowNodeNamePlugin.h \
    core/extend/AlignPlugin.h \
    core/extend/CutPlugin.h \
    core/extend/InvertPortPlugin.h \
    core/extend/AddPortPlugin.h \
    core/extend/RemovePortPlugin.h \
    core/extend/JumpSheetPlugin.h \
    core/extend/ReplaceNodePlugin.h \
    core/model/sheet/Sheet.h \
    core/controller/factory/SheetFactory.h \
    core/model/observer/ProjectObserver.h \
    core/view/widget/SheetListWidget.h \
    core/controller/publisher/SerialNumberNamePublisher.h \
    core/controller/tool/ConnectionReconnectTool.h \
    core/view/dialog/InvertPortDialog.h \
    core/controller/parser/ProjectParser.h \
    core/view/widget/FunctionBlockToolButton.h \
    core/controller/history/SheetChangeHistoryController.h \
    core/model/figure/connection/PolylineConnection.h \
    core/model/figure/connection/AbstractConnection.h \
    core/model/figure/connection/ElbowConnection.h \
    core/view/widget/ConnectionTypeToolButton.h \
    core/view/widget/ToolButtonGroup.h \
    core/view/widget/NodeTypeToolButton.h \
    core/util/JsonUtil.h \
    core/util/ProjectKeyDefine.h \
    core/model/figure/connection/EdgeHandle.h \
    core/model/figure/connection/VertexHandle.h \
    core/controller/tool/VertexEditTool.h \
    core/controller/command/VertexMoveCommand.h \
    core/controller/command/VertexRemoveCommand.h \
    core/extend/VertexRemovePlugin.h \
    core/extend/VertexAddPlugin.h \
    core/controller/command/VertexAddCommand.h \


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
    core/controller/command/ReconnectToPortCommand.cpp \
    core/controller/command/NodeAddCommand.cpp \
    core/controller/command/PortAddCommand.cpp \
    core/controller/command/PortRemoveCommand.cpp \
    core/controller/command/NodeMoveCommand.cpp \
    core/controller/command/NodeRemoveCommand.cpp \
    core/controller/command/NodeReplaceCommand.cpp \
    core/controller/editor/Editor.cpp \
    core/controller/factory/ConnectionFactory.cpp \
    core/controller/factory/ConnectorFactory.cpp \
    core/controller/factory/NodeFactory.cpp \
    core/controller/factory/PortFactory.cpp \
    core/controller/pluginloader/PluginLoader.cpp \
    core/controller/tool/AbstractTool.cpp \
    core/controller/tool/ConnectionCreateTool.cpp \
    core/controller/tool/NodeEditTool.cpp \
    core/controller/tool/SheetJumpTool.cpp \
    core/extend/AbstractPlugin.cpp \
    core/extend/NewPlugin.cpp \
    core/extend/ClosePlugin.cpp \
    core/extend/OpenPlugin.cpp \
    core/extend/QuitPlugin.cpp \
    core/extend/SavePlugin.cpp \
    core/model/figure/connection/Connector.cpp \
    core/model/figure/guideline/GuideLine.cpp \
    core/model/figure/node/AbstractNode.cpp \
    core/model/figure/node/AndNode.cpp \
    core/model/figure/node/InNode.cpp \
    core/model/figure/node/OrNode.cpp \
    core/model/figure/node/OutNode.cpp \
    core/model/figure/node/NotNode.cpp \
    core/model/figure/node/ClockNode.cpp \
    core/model/figure/node/FlipFlopNode.cpp \
    core/model/figure/node/FunctionBlockNode.cpp \
    core/model/figure/port/Port.cpp \
    core/model/observer/SceneObserver.cpp \
    core/model/project/Project.cpp \
    core/model/scene/Scene.cpp \
    core/util/Common.cpp \
    core/util/SystemConfig.cpp \
    core/view/graphicsview/GraphicsView.cpp \
    core/view/menu/MenuManager.cpp \
    core/view/menu/ContextMenuManager.cpp \
    core/view/window/MainWindow.cpp \
    core/extend/ShowNodeNamePlugin.cpp \
    core/extend/AlignPlugin.cpp \
    core/extend/CutPlugin.cpp \
    core/extend/InvertPortPlugin.cpp \
    core/extend/AddPortPlugin.cpp \
    core/extend/RemovePortPlugin.cpp \
    core/extend/JumpSheetPlugin.cpp \
    core/extend/ReplaceNodePlugin.cpp \
    core/model/sheet/Sheet.cpp \
    core/controller/factory/SheetFactory.cpp \
    core/model/observer/ProjectObserver.cpp \
    core/view/widget/SheetListWidget.cpp \
    core/controller/publisher/SerialNumberNamePublisher.cpp \
    core/controller/tool/ConnectionReconnectTool.cpp \
    core/view/dialog/InvertPortDialog.cpp \
    core/controller/parser/ProjectParser.cpp \
    core/view/widget/FunctionBlockToolButton.cpp \
    core/controller/history/SheetChangeHistoryController.cpp \
    core/model/figure/connection/PolylineConnection.cpp \
    core/model/figure/connection/AbstractConnection.cpp \
    core/model/figure/connection/ElbowConnection.cpp \
    core/view/widget/ConnectionTypeToolButton.cpp \
    core/view/widget/ToolButtonGroup.cpp \
    core/view/widget/NodeTypeToolButton.cpp \
    core/util/JsonUtil.cpp \
    core/model/figure/connection/EdgeHandle.cpp \
    core/model/figure/connection/VertexHandle.cpp \
    core/controller/tool/VertexEditTool.cpp \
    core/controller/command/VertexMoveCommand.cpp \
    core/controller/command/VertexRemoveCommand.cpp \
    core/extend/VertexRemovePlugin.cpp \
    core/extend/VertexAddPlugin.cpp \
    core/controller/command/VertexAddCommand.cpp \

FORMS += \
    application/view/widget/DebugControlWidget.ui \
    core/view/window/MainWindow.ui \
    core/view/widget/SheetListWidget.ui \
    core/view/dialog/InvertPortDialog.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
