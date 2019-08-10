#include "Builder.h"

#include "AbstractNode.h"
#include "AndNode.h"
#include "Connection.h"
#include "Define.h"
#include "Editor.h"
#include "InNode.h"
#include "MainWindow.h"
#include "MenuManager.h"
#include "NodeEditTool.h"
#include "NodeFactory.h"
#include "OutNode.h"
#include "PluginLoader.h"
#include "Project.h"
#include "Scene.h"
#include "ui_MainWindow.h"
#include <QAction>
#include <QDebug>
#include <QMenu>
#include <QToolButton>
#include <QUndoStack>

Builder* Builder::getInstance() {
  static Builder s;
  return &s;
}

void Builder::build(MainWindow* mainWindow, Ui::MainWindow* ui) {
  buildGraphicsView(mainWindow, ui);
  buildMenuBar(mainWindow, ui);
  buildToolBar(mainWindow, ui);
  buildWindowTitle(mainWindow, ui);
  //  buildDockWidget(mainWindow, ui);
}

void Builder::buildGraphicsView(MainWindow* mainWindow, Ui::MainWindow* ui) {
  Q_UNUSED(mainWindow);

  ui->graphicsView->setScene(Editor::getInstance()->project()->scene());

  Editor::getInstance()->setGraphicsView(ui->graphicsView);
}

void Builder::buildMenuBar(MainWindow* mainWindow, Ui::MainWindow* ui) {
  Q_UNUSED(mainWindow);

  QMenu* editMenu = MenuManager::getInstance()->menu(MenuManager::MENU_EDIT);

  QAction* undo = Editor::getInstance()->undoStack()->createUndoAction(mainWindow, "Undo");
  undo->setIcon(QIcon("../resource/undo.png"));
  undo->setShortcut(QKeySequence::Undo);
  editMenu->addAction(undo);

  QAction* redo = Editor::getInstance()->undoStack()->createRedoAction(mainWindow, "Redo");
  redo->setShortcut(QKeySequence::Redo);
  redo->setIcon(QIcon("../resource/redo.png"));
  editMenu->addAction(redo);

  PluginLoader::getInstance()->init();
  PluginLoader::getInstance()->load(mainWindow, ui);

  foreach (QMenu* menu, MenuManager::getInstance()->menus()) {
    ui->menuBar->addMenu(menu);
    qDebug() << menu->title();
  }
}

void Builder::buildToolBar(MainWindow* mainWindow, Ui::MainWindow* ui) {
  NodeEditTool* nodeEditTool = dynamic_cast<NodeEditTool*>(Editor::getInstance()->tool(TOOL_NODE_CREATE));
  ui->nodeToolBar->setNodeEditTool(nodeEditTool);

  mainWindow->addToolBar(Qt::LeftToolBarArea, ui->nodeToolBar);
  foreach (QString nodeType, nodeEditTool->nodeTypes()) { ui->nodeToolBar->addToolBarAction(nodeType); }
  ui->nodeToolBar->changeDefaultTool();
}

void Builder::buildWindowTitle(MainWindow* mainWindow, Ui::MainWindow* ui) {
  QObject::connect(Editor::getInstance(), &Editor::projectNameChanged, mainWindow, &MainWindow::setWindowTitle);
}

// void Builder::buildDockWidget(MainWindow *mainWindow, Ui::MainWindow *ui) {
//  AnalyzeCircuitAction *analyzeCircuitAction = dynamic_cast<AnalyzeCircuitAction
//  *>(Editor::getInstance()->action(ACTION_ANALYZE_CIRCUIT));
//  ui->menuBar->addAction(analyzeCircuitAction->ExportScriptAction());

//  QDockWidget *errorDockWidget = analyzeCircuitAction->DockWidget();
//  errorDockWidget->hide();
//  mainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), errorDockWidget);
//}

Builder::Builder() {
}

Builder::~Builder() {
}
