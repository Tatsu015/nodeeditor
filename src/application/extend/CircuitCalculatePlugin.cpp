#include "CircuitCalculatePlugin.h"
#include "AbstractNode.h"
#include "CircuitCalculateExecutor.h"
#include "ClockNode.h"
#include "DataBase.h"
#include "DebugControlWidget.h"
#include "Editor.h"
#include "IOTableWidget.h"
#include "MainWindow.h"
#include "MenuManager.h"
#include "Port.h"
#include "Project.h"
#include "Scene.h"
#include "Sheet.h"
#include "ui_DebugControlWidget.h"
#include "ui_MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <QDockWidget>
#include <QFile>
#include <QMenu>
#include <QStatusBar>

const static QString EXPORT_BASE = "../../Graphics/circuit/data/"; // TODO

CircuitCalculatePlugin::CircuitCalculatePlugin(QObject* parent) : AbstractPlugin(parent) {
}

CircuitCalculatePlugin::~CircuitCalculatePlugin() {
}

void CircuitCalculatePlugin::reset() {
  Editor::getInstance()->project()->scene()->addSceneObserver(m_DebugControlWidget->ui()->tableWidget);
}

void CircuitCalculatePlugin::initView(MainWindow* mainWindow, Ui::MainWindow* ui) {
  Q_UNUSED(ui);
  m_ioSetDockWidget = new QDockWidget();
  m_DebugControlWidget = new DebugControlWidget();
  m_ioSetDockWidget->setWidget(m_DebugControlWidget);
  Editor::getInstance()->project()->scene()->addSceneObserver(m_DebugControlWidget->ui()->tableWidget);
  mainWindow->addDockWidget(Qt::RightDockWidgetArea, m_ioSetDockWidget);
  m_ioSetDockWidget->hide();

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

  QMenu* viewMenu = MenuManager::getInstance()->menu(MenuManager::MENU_VIEW);
  QAction* showDebugControlWidgetAction = m_ioSetDockWidget->toggleViewAction();
  showDebugControlWidgetAction->setText("Show Debug Pain");
  viewMenu->addAction(showDebugControlWidgetAction);
  connect(showDebugControlWidgetAction, &QAction::triggered, this, &CircuitCalculatePlugin::onStartDebug);
}

bool CircuitCalculatePlugin::checkError(const QList<AbstractNode*>& nodes) {
  return checkAllPortFilled(nodes);
}

bool CircuitCalculatePlugin::checkAllPortFilled(const QList<AbstractNode*>& nodes) {
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
CircuitCalculatePlugin::connectedGraphs(const QList<AbstractNode*>& nodes) {
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
      if (connectedNodes.contains(checkNode)) {
        continue;
      }
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

QList<QList<AbstractNode*>>
CircuitCalculatePlugin::loopedNodes(const CircuitCalculatePlugin::ConnectedGraph* connectedGraph) {
  QList<QList<AbstractNode*>> loopNodesList;
  QList<AbstractNode*> inputNodes;

  foreach (AbstractNode* node, connectedGraph->m_nodes) {
    if (Input == node->io()) {
      inputNodes << node;
    }
  }

  foreach (AbstractNode* checkNode, inputNodes) {
    QList<AbstractNode*> usedNodes;
    usedNodes << checkNode;
    foreach (AbstractNode* node, checkNode->adjastOutNodes()) {
      QList<AbstractNode*> loopNodes;
      loopNodes << checkNode;
      if (isAlreadyUsed(node, usedNodes, loopNodes)) {
        QList<AbstractNode*> tmp;
        for (int32_t i = loopNodes.indexOf(node); i < loopNodes.count(); ++i) {
          tmp << loopNodes[i];
        }
        loopNodesList << tmp;
      }
    }
  }

  return loopNodesList;
}

bool CircuitCalculatePlugin::hasLoop(const CircuitCalculatePlugin::ConnectedGraph* connectedGraph) {
  QList<AbstractNode*> usedNodes;
  QList<AbstractNode*> unUsedNodes = connectedGraph->m_nodes;
  AbstractNode* checkNode = unUsedNodes.takeFirst();
  usedNodes << checkNode;

  foreach (AbstractNode* node, checkNode->adjastOutNodes()) {
    if (isAlreadyUsed(node, usedNodes)) {
      return true;
    }
  }

  return false;
}

bool CircuitCalculatePlugin::isAlreadyUsed(AbstractNode* checkNode, QList<AbstractNode*>& usedNodes) {
  if (usedNodes.contains(checkNode)) {
    return true;
  }
  foreach (AbstractNode* node, checkNode->adjastOutNodes()) {
    if (isAlreadyUsed(node, usedNodes)) {
      return true;
    }
    usedNodes << node;
  }
  return false;
}

bool CircuitCalculatePlugin::isAlreadyUsed(AbstractNode* checkNode, QList<AbstractNode*>& usedNodes,
                                           QList<AbstractNode*>& nodes) {
  if (usedNodes.contains(checkNode)) {
    return true;
  }
  usedNodes << checkNode;
  nodes << checkNode;
  foreach (AbstractNode* node, checkNode->adjastOutNodes()) {
    if (isAlreadyUsed(node, usedNodes, nodes)) {
      return true;
    }
    usedNodes << node;
    nodes << node;
  }
  //  nodes.removeOne(checkNode);
  return false;
}

QList<AbstractNode*> CircuitCalculatePlugin::executeOrderSort(CircuitCalculatePlugin::ConnectedGraph* connectedGraph) {
  QList<AbstractNode*> visitedNodes;
  QList<AbstractNode*> unVisitedNodes;
  QList<QList<AbstractNode*>> loopNodes = loopedNodes(connectedGraph);

  foreach (AbstractNode* node, connectedGraph->m_nodes) {
    if (Input == node->io()) {
      visitedNodes << node;
    } else {
      unVisitedNodes << node;
    }
  }
  while (unVisitedNodes.count()) {
    AbstractNode* checkNode = unVisitedNodes.takeLast();
    if (isAllAdjacentInNodeVisited(checkNode, visitedNodes, loopNodes)) {
      visitedNodes << checkNode;
      unVisitedNodes.removeOne(checkNode);
    } else {
      unVisitedNodes.prepend(checkNode);
    }
  }

  return visitedNodes;
}

bool CircuitCalculatePlugin::isAllAdjacentInNodeVisited(AbstractNode* checkNode,
                                                        const QList<AbstractNode*>& visitedNodes,
                                                        QList<QList<AbstractNode*>> loopedNodes) {
  foreach (AbstractNode* inNode, checkNode->adjastInNodes()) {
    if (!visitedNodes.contains(inNode)) {
      foreach (QList<AbstractNode*> loopedNode, loopedNodes) {
        if (!loopedNode.contains(inNode)) {
          return false;
        }
      }
    }
  }
  return true;
}

#include "AbstractConnection.h"
void CircuitCalculatePlugin::compile(QList<AbstractNode*>& nodes) {
  if (!checkError(nodes)) {
    qDebug() << "Do not connect finish!";
    return;
  }

  m_connectedGraphs = connectedGraphs(nodes);
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) {
    //    QList<QList<AbstractNode *>> loopedNode = loopedNodes(connectedGraph);
    //    foreach (QList<AbstractNode *> nodes, loopedNodes(connectedGraph)) {
    //      //      foreach (AbstractNode* node, nodes) { qDebug() <<
    //      node->name(); }
    //    }

    //    if (hasLoop(connectedGraph)) {
    //      qDebug() << "aaaaaaaaaaaaaaaaaaa";
    //    }

    exportCircuit(connectedGraph);
    exportInnitialValue(connectedGraph);
  }
}

void CircuitCalculatePlugin::exportCircuit(ConnectedGraph* connectedGraph) {
  QFile f(EXPORT_BASE + connectedGraph->m_name + ".circuit");
  if (!f.open(QIODevice::WriteOnly)) {
    qDebug() << "Cannot open file!";
  }
  connectedGraph->m_nodes = executeOrderSort(connectedGraph);
  QString buf;
  foreach (AbstractNode* n, connectedGraph->m_nodes) {
    buf += n->name();
    foreach (Port* port, n->ports()) {
      buf += ",";
      AbstractConnection* connection = port->connections().first();
      if (CLOCK == connection->startPort()->parentNode()->nodeType()) {
        buf += CLOCK;
      } else {
        buf += port->connections().first()->id();
      }
    }
    buf += "\n";
  }
  f.write(buf.toLocal8Bit());
}

void CircuitCalculatePlugin::exportInnitialValue(CircuitCalculatePlugin::ConnectedGraph* connectedGraph) {
  QFile f(EXPORT_BASE + connectedGraph->m_name + ".initial");
  if (!f.open(QIODevice::WriteOnly)) {
    qDebug() << "Cannot open file!";
  }
  QList<AbstractConnection*> connections;
  foreach (AbstractNode* n, connectedGraph->m_nodes) {
    foreach (Port* port, n->ports()) {
      foreach (AbstractConnection* connection, port->connections()) {
        if (!connections.contains(connection)) {
          connections << connection;
        }
      }
    }
  }

  QString buf;
  foreach (AbstractConnection* connection, connections) {
    buf += connection->id() + ",false";
    buf += "\n";
  }

  f.write(buf.toLocal8Bit());
}

void CircuitCalculatePlugin::tearDown() {
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) {
    foreach (AbstractNode* node, connectedGraph->m_nodes) { node->resetColor(); }
  }
  startDebug("", 0);
  m_DebugControlWidget->tearDown();
}

void CircuitCalculatePlugin::onCompile() {
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->activeSheet()->nodes();
  compile(nodes);
}

void CircuitCalculatePlugin::onRun() {
  CircuitCalculateExecutor::getInstance()->teardownStack();
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->activeSheet()->nodes();
  compile(nodes);

  QList<AbstractNode*> nodeStack;
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) { nodeStack.append(connectedGraph->m_nodes); }
  CircuitCalculateExecutor::getInstance()->setupStack(nodeStack);
  CircuitCalculateExecutor::getInstance()->run();
  m_DebugControlWidget->ui()->tableWidget->read();
  tearDown();
}

void CircuitCalculatePlugin::onStartDebug() {
  QList<AbstractNode*> nodes = Editor::getInstance()->project()->activeSheet()->nodes();
  compile(nodes);
  CircuitCalculateExecutor::getInstance()->teardownStack();
  m_DebugControlWidget->setup();

  QList<AbstractNode*> nodeStack;
  foreach (ConnectedGraph* connectedGraph, m_connectedGraphs) { nodeStack.append(connectedGraph->m_nodes); }
  CircuitCalculateExecutor::getInstance()->setupStack(nodeStack);
  m_ioSetDockWidget->show();
  startDebug("Debug start", 1000);
}

void CircuitCalculatePlugin::onStopDebug() {
  tearDown();
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
