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
#include "ui_MainWindow.h"

CircuitCalculatePlugin::CircuitCalculatePlugin() : AbstractPlugin() {}

CircuitCalculatePlugin::~CircuitCalculatePlugin() {}

void CircuitCalculatePlugin::initView(MainWindow* mainWindow, Ui::MainWindow* ui) {
  QDockWidget* ioSetDockWidget = new QDockWidget();
  m_ioTableWidget = new IOTableWidget();
  ioSetDockWidget->setWidget(m_ioTableWidget);
  Editor::getInstance()->project()->scene()->addSceneObserver(m_ioTableWidget);
  mainWindow->addDockWidget(Qt::RightDockWidgetArea, ioSetDockWidget);
}

void CircuitCalculatePlugin::doInit() {
  QMenu* buildMenu = new QMenu("Build");
  QAction* runAction = new QAction("Run");
  runAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
  buildMenu->addAction(runAction);
  MenuManager::getInstance()->addMenu(buildMenu);
  connect(runAction, &QAction::triggered, this, &CircuitCalculatePlugin::onRun);

  QMenu* debugMenu = new QMenu("Debug");
  QAction* debugAction = new QAction("Start Debug");
  debugAction->setShortcut(QKeySequence(Qt::Key_F5));
  debugMenu->addAction(debugAction);
  MenuManager::getInstance()->addMenu(debugMenu);
  connect(debugAction, &QAction::triggered, this, &CircuitCalculatePlugin::onDebug);
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

#include "DataBase.h"
void CircuitCalculatePlugin::onRun() {
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();

  if (!CheckError(nodes)) {
    qDebug() << "Do not connect finish!";
    return;
  }
  QList<ConnectedGraph*> connectedGtaphs = ConnectedGraphs(nodes);
  foreach (ConnectedGraph* connectedGtaph, connectedGtaphs) {
    QList<AbstractNode*> sortedNodes = ExecuteOrderSort(connectedGtaph);
    foreach (AbstractNode* node, sortedNodes) {
      QList<bool> args;
      if(0 == node->adjastInNodes().count()){
        args << DataBase::getInstance()->read(node->name());
      }
      else{
        foreach (AbstractNode* inNode, node->adjastInNodes()) {
          args << DataBase::getInstance()->read(inNode->name());
        }
      }
      DataBase::getInstance()->write(node->name(), node->execute(args));
    }
  }
  m_ioTableWidget->read();
}

void CircuitCalculatePlugin::onDebug()
{
  qDebug() << " FIXME Debug";
}
