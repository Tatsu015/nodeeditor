#include "CircuitCalculatePlugin.h"
#include "AbstractNode.h"
#include "CircuitCalculateExecutor.h"
#include "DataBase.h"
#include "DebugControlWidget.h"
#include "Editor.h"
#include "IOTableWidget.h"
#include "MainWindow.h"
#include "MenuManager.h"
#include "Port.h"
#include "Project.h"
#include "Scene.h"
#include "ui_DebugControlWidget.h"
#include "ui_MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <QDockWidget>
#include <QMenu>
#include <QStatusBar>

CircuitCalculatePlugin::CircuitCalculatePlugin(QObject* parent) : AbstractPlugin(parent) {
}

CircuitCalculatePlugin::~CircuitCalculatePlugin() {
}

void CircuitCalculatePlugin::reset() {
  Editor::getInstance()->project()->scene()->addSceneObserver(m_DebugControlWidget->ui()->tableWidget);
}

void CircuitCalculatePlugin::initView(MainWindow* mainWindow, Ui::MainWindow* ui) {
  Q_UNUSED(ui);
  QDockWidget* ioSetDockWidget = new QDockWidget();
  m_DebugControlWidget = new DebugControlWidget();
  ioSetDockWidget->setWidget(m_DebugControlWidget);
  Editor::getInstance()->project()->scene()->addSceneObserver(m_DebugControlWidget->ui()->tableWidget);
  mainWindow->addDockWidget(Qt::RightDockWidgetArea, ioSetDockWidget);

  connect(m_DebugControlWidget->ui()->startDebugButton, &QToolButton::clicked, this,
          &CircuitCalculatePlugin::onStartDebug);
  connect(m_DebugControlWidget->ui()->stepOverButton, &QToolButton::clicked, this, &CircuitCalculatePlugin::onStepOver);
  connect(m_DebugControlWidget->ui()->stopDebugButton, &QToolButton::clicked, this,
          &CircuitCalculatePlugin::onStopDebug);
  connect(this, &CircuitCalculatePlugin::startDebug, ui->statusBar, &QStatusBar::showMessage);
}

void CircuitCalculatePlugin::doInit() {
  QMenu* buildMenu = new QMenu("Build");

  QAction* compileAction = new QAction(QIcon("../resource/compile.png"), "Compile");
  compileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
  buildMenu->addAction(compileAction);
  connect(compileAction, &QAction::triggered, this, &CircuitCalculatePlugin::onCompile);

  QAction* runAction = new QAction(QIcon("../resource/run.png"), "Run");
  runAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  buildMenu->addAction(runAction);
  connect(runAction, &QAction::triggered, this, &CircuitCalculatePlugin::onRun);

  QMenu* debugMenu = new QMenu("Debug");
  QAction* debugAction = new QAction(QIcon("../resource/debug.png"), "Start Debug");
  debugAction->setShortcut(QKeySequence(Qt::Key_F5));
  debugMenu->addAction(debugAction);
  connect(debugAction, &QAction::triggered, this, &CircuitCalculatePlugin::onStartDebug);

  MenuManager::getInstance()->addMenu(buildMenu);
  MenuManager::getInstance()->addMenu(debugMenu);
}

bool CircuitCalculatePlugin::CheckError(const QList<AbstractNode*>& nodes) {
  return CheckAllPortFilled(nodes);
}

bool CircuitCalculatePlugin::CheckAllPortFilled(const QList<AbstractNode*>& nodes) {
  bool ret = true;
  foreach (AbstractNode* node, nodes) {
    foreach (Port* port, node->ports()) {
      if (0 == port->connections().count()) {
        //          QString msg = BASE_MESSAGE + node->name();
        //          m_listWidget->onAddErrorWidgetItem(node, msg, Error);
        ret = false;
      }
    }
  }
  return ret;
}

QList<CircuitCalculatePlugin::ConnectedGraph*>
CircuitCalculatePlugin::ConnectedGraphs(const QList<AbstractNode*>& nodes) {
  QList<ConnectedGraph*> connectedGraphs;
  QList<AbstractNode*> unusedNode = nodes;
  uint64_t id = 0;

  while (unusedNode.count()) {
    QList<AbstractNode*> connectedNodes;
    AbstractNode* node = unusedNode.last();
    QList<AbstractNode*> unvisitedNodes;
    unvisitedNodes << node;

    while (unvisitedNodes.count()) {
      AbstractNode* checkNode = unvisitedNodes.takeLast();
      connectedNodes << checkNode;
      unusedNode.removeOne(checkNode);
      foreach (AbstractNode* adjastNode, checkNode->adjastNodes()) {
        if (!connectedNodes.contains(adjastNode)) {
          unvisitedNodes << adjastNode;
        }
      }
    }
    ConnectedGraph* connectedGraph = new ConnectedGraph();
    connectedGraph->m_nodes = connectedNodes;
    connectedGraph->m_id = ++id;
    connectedGraph->m_name = "f_" + QString::number(id);
    connectedGraphs << connectedGraph;
  }

  return connectedGraphs;
}

QList<AbstractNode*> CircuitCalculatePlugin::ExecuteOrderSort(CircuitCalculatePlugin::ConnectedGraph* connectedGraph) {
  QList<AbstractNode*> visitedNodes;
  QList<AbstractNode*> unVisitedNodes;
  foreach (AbstractNode* node, connectedGraph->m_nodes) {
    if (Input == node->io()) {
      visitedNodes << node;
    } else {
      unVisitedNodes << node;
    }
  }
  while (unVisitedNodes.count()) {
    AbstractNode* checkNode = unVisitedNodes.last();
    if (isAllAdjacentInNodeVisited(checkNode, visitedNodes)) {
      visitedNodes << checkNode;
      unVisitedNodes.removeOne(checkNode);
    }
  }

  qDebug() << "--------------------------------";
  foreach (AbstractNode* node, visitedNodes) { qDebug() << node->name(); }
  return visitedNodes;
}

bool CircuitCalculatePlugin::isAllAdjacentInNodeVisited(AbstractNode* checkNode,
                                                        const QList<AbstractNode*>& visitedNodes) {
  foreach (AbstractNode* inNode, checkNode->adjastInNodes()) {
    if (!visitedNodes.contains(inNode)) {
      return false;
    }
  }
  return true;
}

void CircuitCalculatePlugin::compile(QList<AbstractNode*>& nodes) {
  if (!CheckError(nodes)) {
    qDebug() << "Do not connect finish!";
    return;
  }

  m_connectedGraphs = ConnectedGraphs(nodes);
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) {
    connectedGraph->m_nodes = ExecuteOrderSort(connectedGraph);
  }
}

void CircuitCalculatePlugin::tearDown() {
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) {
    foreach (AbstractNode* node, connectedGraph->m_nodes) { node->resetColor(); }
  }
  startDebug("", 0);
  m_DebugControlWidget->tearDown();
}

void CircuitCalculatePlugin::onCompile() {
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();
  compile(nodes);
}

void CircuitCalculatePlugin::onRun() {
  CircuitCalculateExecutor::getInstance()->teardownStack();
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();
  compile(nodes);

  QList<AbstractNode*> nodeStack;
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) { nodeStack.append(connectedGraph->m_nodes); }
  CircuitCalculateExecutor::getInstance()->setupStack(nodeStack);
  CircuitCalculateExecutor::getInstance()->run();
  m_DebugControlWidget->ui()->tableWidget->read();
  tearDown();
}

void CircuitCalculatePlugin::onStartDebug() {
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();
  compile(nodes);
  CircuitCalculateExecutor::getInstance()->teardownStack();
  m_DebugControlWidget->setup();

  QList<AbstractNode*> nodeStack;
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) { nodeStack.append(connectedGraph->m_nodes); }
  CircuitCalculateExecutor::getInstance()->setupStack(nodeStack);
  m_DebugControlWidget->show();
  startDebug("Debug start", 1000);
}

void CircuitCalculatePlugin::onStepOver() {
  if (0 == CircuitCalculateExecutor::getInstance()->stackCount()) {
    tearDown();
    return;
  }
  CircuitCalculateExecutor::getInstance()->stepOver();
  m_DebugControlWidget->ui()->tableWidget->read();
}

void CircuitCalculatePlugin::onNext() {
  if (0 == CircuitCalculateExecutor::getInstance()->stackCount()) {
    tearDown();
    return;
  }
  CircuitCalculateExecutor::getInstance()->stepOver();
  m_DebugControlWidget->ui()->tableWidget->read();
}

void CircuitCalculatePlugin::onStopDebug() {
  tearDown();
}