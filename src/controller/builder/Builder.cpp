#include "Builder.h"

#include <QAction>
#include <QDebug>
#include <QMenu>
#include <QToolButton>
#include "AbstractAction.h"
#include "AbstractNode.h"
#include "AnalyzeCircuitAction.h"
#include "Connection.h"
#include "ConnectionFactory.h"
#include "Define.h"
#include "Editor.h"
#include "ErrorListWidget.h"
#include "HiddenNode.h"
#include "InNode.h"
#include "MainWindow.h"
#include "NodeCreateTool.h"
#include "NodeFactory.h"
#include "OutNode.h"
#include "Scene.h"
#include "Tool.h"
#include "ui_MainWindow.h"

Builder *Builder::getInstance() {
  static Builder s;
  return &s;
}

void Builder::build(MainWindow *mainWindow, Ui::MainWindow *ui) {
  buildGraphicsView(mainWindow, ui);
  buildMenu(mainWindow, ui);
  buildToolBar(mainWindow, ui);
  buildDockWidget(mainWindow, ui);
}

void Builder::buildGraphicsView(MainWindow *mainWindow, Ui::MainWindow *ui) {
  Q_UNUSED(mainWindow);

  ui->graphicsView->setBackgroundBrush(QBrush(QColor(75, 75, 75)));
  ui->graphicsView->setRenderHints(QPainter::Antialiasing);
}

void Builder::buildMenu(MainWindow *mainWindow, Ui::MainWindow *ui) {
  Q_UNUSED(mainWindow);

  QMenu *fileMenu = new QMenu("File");
  ui->menuBar->addMenu(fileMenu);
  fileMenu->addAction(Editor::getInstance()->action(ACTION_OPEN)->action());
  fileMenu->addAction(Editor::getInstance()->action(ACTION_SAVE)->action());

  QMenu *viewMenu = new QMenu("View");
  ui->menuBar->addMenu(viewMenu);
  QMenu *dockMenu = new QMenu("Dock");
  viewMenu->addMenu(dockMenu);
  AnalyzeCircuitAction *ep = dynamic_cast<AnalyzeCircuitAction *>(Editor::getInstance()->action(ACTION_ANALYZE_CIRCUIT));
  dockMenu->addAction(ep->DockWidget()->toggleViewAction());
}

void Builder::buildToolBar(MainWindow *mainWindow, Ui::MainWindow *ui) {
  // setup tool bar
  NodeCreateTool *nodeCreationTool = dynamic_cast<NodeCreateTool *>(Editor::getInstance()->tool("NODE"));
  ui->nodeToolBar->setNodeCreationTool(nodeCreationTool);

  mainWindow->addToolBar(Qt::LeftToolBarArea, ui->nodeToolBar);
  foreach (QString nodeType, nodeCreationTool->nodeTypes()) { ui->nodeToolBar->addToolBarAction(nodeType); }
}

void Builder::buildDockWidget(MainWindow *mainWindow, Ui::MainWindow *ui) {
  AnalyzeCircuitAction *ep = dynamic_cast<AnalyzeCircuitAction *>(Editor::getInstance()->action(ACTION_ANALYZE_CIRCUIT));
  ui->menuBar->addAction(ep->ExportScriptAction());

  mainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), ep->DockWidget());
}

void Builder::setDefaultToolBarAction(QString actionName) {
  Tool::getInstance()->changeActiveTool(actionName);
  QAction *acr = m_toolBarActions[actionName]->m_action;
  acr->setChecked(true);
}

void Builder::onChangeTool() {
  QString toolName = dynamic_cast<QAction *>(sender())->text();
  Tool::getInstance()->changeActiveTool(toolName);
}

Builder::Builder(QObject *parent) : QObject(parent) {}

Builder::~Builder() {}
