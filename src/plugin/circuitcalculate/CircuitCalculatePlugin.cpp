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
  IOTableWidget* ioTableWidget = new IOTableWidget();
  ioSetDockWidget->setWidget(ioTableWidget);
  Editor::getInstance()->project()->scene()->addSceneObserver(ioTableWidget);
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
    QList<AbstractNode*> unvisitedNodes = connectedGraph->m_nodes;

    while (unvisitedNodes.count()) {
      AbstractNode* visitNode = unvisitedNodes.takeLast();
      visitedNodes << visitNode;
      foreach (AbstractNode* adjastInNode, visitNode->adjastInNodes()) {
        if (!visitedNodes.contains(adjastInNode)) {
          unvisitedNodes.append(adjastInNode);
        } else {
          visitedNodes.move(visitedNodes.indexOf(visitNode), visitedNodes.indexOf(adjastInNode));
        }
      }
    }

    std::reverse(visitedNodes.begin(), visitedNodes.end());
    qDebug() << "======  " + connectedGraph->m_name + " ======";
    foreach (AbstractNode* node, visitedNodes) { qDebug() << node->name(); }
    return visitedNodes;
}

void CircuitCalculatePlugin::onRun() {
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->scene()->nodes();

  if (!CheckError(nodes)) {
    qDebug() << "Do not connect finish!";
    return;
  }
  QList<ConnectedGraph*> connectedGtaphs = ConnectedGraphs(nodes);
  foreach (ConnectedGraph* connectedGtaph, connectedGtaphs) { ExecuteOrderSort(connectedGtaph); }
}

void CircuitCalculatePlugin::onDebug()
{
  qDebug() << " FIXME Debug";
}
