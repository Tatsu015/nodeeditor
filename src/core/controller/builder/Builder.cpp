#include "Builder.h"
#include "ConnectionTypeToolButton.h"
#include "Define.h"
#include "Editor.h"
#include "FunctionBlockToolButton.h"
#include "MainWindow.h"
#include "MenuManager.h"
#include "NodeFactory.h"
#include "NodeTypeToolButton.h"
#include "PluginLoader.h"
#include "Project.h"
#include "Scene.h"
#include "SheetListWidget.h"
#include "ToolButtonGroup.h"
#include "ui_MainWindow.h"
#include <QAction>
#include <QMenu>
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
  buildDockWidget(mainWindow, ui);
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

  PluginLoader::getInstance()->init(mainWindow, ui);

  foreach (QMenu* menu, MenuManager::getInstance()->menus()) { ui->menuBar->addMenu(menu); }
}

void Builder::buildToolBar(MainWindow* mainWindow, Ui::MainWindow* ui) {
  Q_UNUSED(mainWindow);

  ToolButtonGroup* group = new ToolButtonGroup(ui->toolBar);

  foreach (QString nodeType, NodeFactory::getInstance()->nodeTypes()) {
    NodeTypeToolButton* nodeTypeToolButton = new NodeTypeToolButton(nodeType);
    ui->toolBar->addWidget(nodeTypeToolButton);
    group->add(nodeTypeToolButton);
  }

  ui->toolBar->addSeparator();

  FunctionBlockToolButton* toolButton = new FunctionBlockToolButton();
  ui->toolBar->addWidget(toolButton);
  group->add(toolButton);
  Editor::getInstance()->project()->addObserver(toolButton);

  ui->toolBar->addSeparator();

  ConnectionTypeToolButton* connectionTypeToolButton = new ConnectionTypeToolButton();
  connectionTypeToolButton->setup();
  ui->toolBar->addWidget(connectionTypeToolButton);

  group->activateDefault();
}

void Builder::buildWindowTitle(MainWindow* mainWindow, Ui::MainWindow* ui) {
  QObject::connect(Editor::getInstance(), &Editor::projectNameChanged, mainWindow, &MainWindow::setWindowTitle);
}

void Builder::buildDockWidget(MainWindow* mainWindow, Ui::MainWindow* ui) {
  SheetListWidget* sheetListWidget = new SheetListWidget();
  ui->sheetDockWidget->setWidget(sheetListWidget);
  Editor::getInstance()->project()->addObserver(sheetListWidget);
  //  AnalyzeCircuitAction *analyzeCircuitAction = dynamic_cast<AnalyzeCircuitAction
  //  *>(Editor::getInstance()->action(ACTION_ANALYZE_CIRCUIT));
  //  ui->menuBar->addAction(analyzeCircuitAction->ExportScriptAction());

  //  QDockWidget *errorDockWidget = analyzeCircuitAction->DockWidget();
  //  errorDockWidget->hide();
  //  mainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), errorDockWidget);
}

Builder::Builder() {
}

Builder::~Builder() {
}
