#include "CircuitCalculatePlugin.h"
#include <QApplication>
#include <QDockWidget>
#include <QMenu>
#include <QDebug>
#include "Editor.h"
#include "IOTableWidget.h"
#include "MainWindow.h"
#include "MenuManager.h"
#include "Project.h"
#include "Scene.h"
#include "AbstractNode.h"
#include "Port.h"
#include "DataBase.h"
#include "DebugControlDialog.h"
#include "ui_MainWindow.h"
#include "ui_DebugControlDialog.h"

CircuitCalculatePlugin::CircuitCalculatePlugin(QObject* parent) : AbstractPlugin(parent) {}

CircuitCalculatePlugin::~CircuitCalculatePlugin() {}

void CircuitCalculatePlugin::reset()
{
  Editor::getInstance()->project()->scene()->addSceneObserver(m_ioTableWidget);
}

void CircuitCalculatePlugin::initView(MainWindow* mainWindow, Ui::MainWindow* ui) {
  Q_UNUSED(ui);
  QDockWidget* ioSetDockWidget = new QDockWidget();
  m_ioTableWidget = new IOTableWidget();
  ioSetDockWidget->setWidget(m_ioTableWidget);
  Editor::getInstance()->project()->scene()->addSceneObserver(m_ioTableWidget);
  mainWindow->addDockWidget(Qt::RightDockWidgetArea, ioSetDockWidget);

  m_debugControlDialog = new DebugControlDialog();
  connect(m_debugControlDialog->ui()->toolButton, &QToolButton::clicked,
          this, &CircuitCalculatePlugin::onProgress);

}

void CircuitCalculatePlugin::doInit() {
  QMenu* buildMenu = new QMenu("Build");

  QAction* compileAction = new QAction("Compile");
  compileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
  buildMenu->addAction(compileAction);
  connect(compileAction, &QAction::triggered, this, &CircuitCalculatePlugin::onCompile);

  QAction* runAction = new QAction("Run");
  runAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  buildMenu->addAction(runAction);
  connect(runAction, &QAction::triggered, this, &CircuitCalculatePlugin::onRun);

  QMenu* debugMenu = new QMenu("Debug");
  QAction* debugAction = new QAction("Start Debug");
  debugAction->setShortcut(QKeySequence(Qt::Key_F5));
  debugMenu->addAction(debugAction);
  connect(debugAction, &QAction::triggered, this, &CircuitCalculatePlugin::onDebug);

  MenuManager::getInstance()->addMenu(buildMenu);
  MenuManager::getInstance()->addMenu(debugMenu);
}

bool CircuitCalculatePlugin::CheckError(const QList<AbstractNode*>& nodes)
{
  return CheckAllPortFilled(nodes);
}

bool CircuitCalculatePlugin::CheckAllPortFilled(const QList<AbstractNode*>& nodes)
{
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

QList<CircuitCalculatePlugin::ConnectedGraph*> CircuitCalculatePlugin::ConnectedGraphs(const QList<AbstractNode*>& nodes)
{
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

QList<AbstractNode*> CircuitCalculatePlugin::ExecuteOrderSort(CircuitCalculatePlugin::ConnectedGraph* connectedGraph)
{
  QList<AbstractNode*> visitedNodes;
  QList<AbstractNode*> unVisitedNodes;
  foreach (AbstractNode* node, connectedGraph->m_nodes) {
    if(Input == node->io()){
      visitedNodes << node;
    }
    else{
      unVisitedNodes << node;
    }
  }
  while (unVisitedNodes.count()) {
    AbstractNode* checkNode = unVisitedNodes.last();
    if(isAllAdjacentInNodeVisited(checkNode, visitedNodes)){
      visitedNodes << checkNode;
      unVisitedNodes.removeOne(checkNode);
    }
  }

  qDebug() << "--------------------------------";
  foreach (AbstractNode* node, visitedNodes) { qDebug() << node->name(); }
  return visitedNodes;
}

bool CircuitCalculatePlugin::isAllAdjacentInNodeVisited(AbstractNode* checkNode, const QList<AbstractNode*>& visitedNodes)
{
  foreach (AbstractNode* inNode, checkNode->adjastInNodes()) {
    if(!visitedNodes.contains(inNode)){
      return false;
    }
  }
  return true;
}

void CircuitCalculatePlugin::compile(QList<AbstractNode*>& nodes)
{
  if (!CheckError(nodes)) {
    qDebug() << "Do not connect finish!";
    return;
  }
  m_connectedGraphs = ConnectedGraphs(nodes);
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) {
    connectedGraph->m_nodes = ExecuteOrderSort(connectedGraph);
  }
}

void CircuitCalculatePlugin::run(QList<AbstractNode*>& nodes)
{
  foreach (AbstractNode* node, nodes) {
    QList<bool> args = arguments(node);
    bool result = node->execute(args);
    node->setToolTip(btos(result));

    DataBase::getInstance()->write(node->name(), result);
  }
}

QList<bool> CircuitCalculatePlugin::arguments(AbstractNode* node)
{
  QList<bool> args;
  if(0 == node->adjastInNodes().count()){
    args << DataBase::getInstance()->read(node->name());
  }
  else{
    foreach (AbstractNode* inNode, node->adjastInNodes()) {
      args << DataBase::getInstance()->read(inNode->name());
    }
  }
  return args;
}

void CircuitCalculatePlugin::onCompile()
{
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();
  compile(nodes);
}

void CircuitCalculatePlugin::onRun() {
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();
  compile(nodes);

  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) {
    run(connectedGraph->m_nodes);
  }
  m_ioTableWidget->read();
}

void CircuitCalculatePlugin::onDebug()
{
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();
  compile(nodes);
  m_executeNodeStack.clear();
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) {
    m_executeNodeStack.append(connectedGraph->m_nodes);
  }
  m_debugControlDialog->show();
}

void CircuitCalculatePlugin::onProgress()
{
  if(0 == m_executeNodeStack.count()){
    m_debugControlDialog->hide();
    return;
  }
  AbstractNode* node = m_executeNodeStack.takeFirst();
  node->setBrush(Qt::red);
  QList<bool> args = arguments(node);
  bool result = node->execute(args);
  node->setToolTip(btos(result));

  DataBase::getInstance()->write(node->name(), result);
  m_ioTableWidget->read();
}
