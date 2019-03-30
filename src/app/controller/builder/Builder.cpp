#include "Builder.h"

#include <QAction>
#include <QDebug>
#include <QMenu>
#include <QToolButton>
#include <QUndoStack>
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

Builder *Builder::getInstance() {
  static Builder s;
  return &s;
}

void Builder::build(MainWindow *mainWindow, Ui::MainWindow *ui) {
  buildGraphicsView(mainWindow, ui);
  buildDefaultMenu(mainWindow, ui);
  buildToolBar(mainWindow, ui);
  buildWindowTitle(mainWindow, ui);
  //  buildDockWidget(mainWindow, ui);
  PluginLoader::getInstance()->init();
  PluginLoader::getInstance()->load(mainWindow, ui);

}

void Builder::buildGraphicsView(MainWindow *mainWindow, Ui::MainWindow *ui) {
  Q_UNUSED(mainWindow);

  ui->graphicsView->setScene(Editor::getInstance()->project()->scene());

  Editor::getInstance()->setGraphicsView(ui->graphicsView);
}

void Builder::buildDefaultMenu(MainWindow *mainWindow, Ui::MainWindow *ui) {
  Q_UNUSED(mainWindow);

  QMenu* fileMenu = new QMenu(MenuManager::MENU_FILE);
  MenuManager::getInstance()->addMenu(fileMenu);

  QMenu* editMenu = new QMenu(MenuManager::MENU_EDIT);
  MenuManager::getInstance()->addMenu(editMenu);

  QMenu* viewMenu = new QMenu(MenuManager::MENU_VIEW);
  MenuManager::getInstance()->addMenu(viewMenu);


  QAction *undo = Editor::getInstance()->undoStack()->createUndoAction(mainWindow, "Undo");
  undo->setIcon(QIcon("../resource/undo.png"));
  undo->setShortcut(QKeySequence::Undo);
  editMenu->addAction(undo);

  QAction *redo = Editor::getInstance()->undoStack()->createRedoAction(mainWindow, "Redo");
  redo->setShortcut(QKeySequence::Redo);
  redo->setIcon(QIcon("../resource/redo.png"));
  editMenu->addAction(redo);

  foreach (QMenu *menu, MenuManager::getInstance()->menus()) { ui->menuBar->addMenu(menu); }
}

void Builder::buildToolBar(MainWindow *mainWindow, Ui::MainWindow *ui) {
  NodeEditTool *nodeEditTool = dynamic_cast<NodeEditTool *>(Editor::getInstance()->tool(TOOL_NODE_CREATE));
  ui->nodeToolBar->setNodeEditTool(nodeEditTool);

  mainWindow->addToolBar(Qt::LeftToolBarArea, ui->nodeToolBar);
  foreach (QString nodeType, nodeEditTool->nodeTypes()) { ui->nodeToolBar->addToolBarAction(nodeType); }
}

void Builder::buildWindowTitle(MainWindow *mainWindow, Ui::MainWindow *ui) {
  QObject::connect(Editor::getInstance(), &Editor::projectNameChanged, mainWindow, &MainWindow::setWindowTitle);
}

// void Builder::buildDockWidget(MainWindow *mainWindow, Ui::MainWindow *ui) {
//  AnalyzeCircuitAction *analyzeCircuitAction = dynamic_cast<AnalyzeCircuitAction *>(Editor::getInstance()->action(ACTION_ANALYZE_CIRCUIT));
//  ui->menuBar->addAction(analyzeCircuitAction->ExportScriptAction());

//  QDockWidget *errorDockWidget = analyzeCircuitAction->DockWidget();
//  errorDockWidget->hide();
//  mainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), errorDockWidget);
//}

Builder::Builder() {}

Builder::~Builder() {}
