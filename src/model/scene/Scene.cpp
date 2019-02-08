#include "Scene.h"
#include <QCursor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QKeyEvent>
#include "AbstractTool.h"
#include "AndNode.h"
#include "Connection.h"
#include "ConnectionFactory.h"
#include "Connector.h"
#include "Define.h"
#include "Editor.h"
#include "InNode.h"
#include "GuideLine.h"
#include "NodeEditTool.h"
#include "NodeFactory.h"
#include "OutNode.h"
#include "Port.h"
#include "Tool.h"
#include "Common.h"

const static qreal TORELANCE = 5;

Scene::Scene(QObject* parent) : QGraphicsScene(-750, -1000, 2000, 2000, parent), m_isControlPressed(false) {
  addLine(-1000, 0, 1000, 0, QPen(Qt::gray));
  addLine(0, -1000, 0, 1000, QPen(Qt::gray));

  //    AutoSet();
}

Scene::~Scene() {}

void Scene::autoSet() {
  QGraphicsSceneMouseEvent event;

  Tool::getInstance()->changeActiveTool("In");
  event.setScenePos(QPointF(0, 0));
  mouseDoubleClickEvent(&event);
  event.setScenePos(QPointF(0, 50));
  mouseDoubleClickEvent(&event);

  Tool::getInstance()->changeActiveTool("Hidden");
  event.setScenePos(QPointF(100, 25));
  mouseDoubleClickEvent(&event);
  event.setScenePos(QPointF(200, 75));
  mouseDoubleClickEvent(&event);

  Tool::getInstance()->changeActiveTool("Out");
  event.setScenePos(QPointF(400, 0));
  mouseDoubleClickEvent(&event);
  event.setScenePos(QPointF(400, 100));
  mouseDoubleClickEvent(&event);

  Tool::getInstance()->changeActiveTool("In");
  event.setScenePos(QPointF(0, 125));
  mouseDoubleClickEvent(&event);

  Tool::getInstance()->changeActiveTool("Hidden");
  event.setScenePos(QPointF(300, 100));
  mouseDoubleClickEvent(&event);

  event.setScenePos(m_nodes[0]->ports().at(0)->centerScenePos());
  mousePressEvent(&event);
  event.setScenePos(m_nodes[2]->ports().at(0)->centerScenePos());
  mouseReleaseEvent(&event);

  event.setScenePos(m_nodes[1]->ports().at(0)->centerScenePos());
  mousePressEvent(&event);
  event.setScenePos(m_nodes[2]->ports().at(1)->centerScenePos());
  mouseReleaseEvent(&event);

  event.setScenePos(m_nodes[2]->ports().at(2)->centerScenePos());
  mousePressEvent(&event);
  event.setScenePos(m_nodes[3]->ports().at(0)->centerScenePos());
  mouseReleaseEvent(&event);

  event.setScenePos(m_nodes[2]->ports().at(2)->centerScenePos());
  mousePressEvent(&event);
  event.setScenePos(m_nodes[4]->ports().at(0)->centerScenePos());
  mouseReleaseEvent(&event);

  event.setScenePos(m_nodes[6]->ports().at(0)->centerScenePos());
  mousePressEvent(&event);
  event.setScenePos(m_nodes[7]->ports().at(1)->centerScenePos());
  mouseReleaseEvent(&event);

  event.setScenePos(m_nodes[3]->ports().at(2)->centerScenePos());
  mousePressEvent(&event);
  event.setScenePos(m_nodes[7]->ports().at(0)->centerScenePos());
  mouseReleaseEvent(&event);

  event.setScenePos(m_nodes[7]->ports().at(2)->centerScenePos());
  mousePressEvent(&event);
  event.setScenePos(m_nodes[5]->ports().at(0)->centerScenePos());
  mouseReleaseEvent(&event);

  event.setScenePos(m_nodes[7]->ports().at(2)->centerScenePos());
  mousePressEvent(&event);
  event.setScenePos(m_nodes[3]->ports().at(1)->centerScenePos());
  mouseReleaseEvent(&event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  changeActiveTool(event->scenePos());
  Editor::getInstance()->activeTool()->mousePressEvent(this, event);
  QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  changeActiveTool(event->scenePos());
  Editor::getInstance()->activeTool()->mouseMoveEvent(this, event);
  QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  Editor::getInstance()->activeTool()->mouseReleaseEvent(this, event);
  Editor::getInstance()->changeDefaultTool();
  QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
  Editor::getInstance()->activeTool()->mouseDoubleClickEvent(this, event);
  QGraphicsScene::mouseDoubleClickEvent(event);
}

void Scene::keyPressEvent(QKeyEvent* event) {
  if (Qt::Key_Delete == event->key()) {
    foreach (QGraphicsItem* item, selectedItems()) { removeNode(dynamic_cast<AbstractNode*>(item)); }
  } else if (Qt::Key_Control == event->key()) {
    m_isControlPressed = true;
  } else if (Qt::Key_A == event->key()) {
    if (m_isControlPressed) {
      foreach (AbstractNode* node, nodes()) { node->setSelected(true); }
    }
  }

  QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent* event) {
  if (Qt::Key_Control == event->key()) {
    m_isControlPressed = false;
  }

  QGraphicsScene::keyReleaseEvent(event);
}

Port* Scene::findPort(QPointF scenePos) {
  QPointF offset = QPointF(2, 2);
  QRectF searchArea = QRectF(scenePos - offset, scenePos + offset);
  QList<QGraphicsItem*> pressedItems = items(searchArea);

  Port* port = nullptr;
  foreach (QGraphicsItem* item, pressedItems) {
    port = dynamic_cast<Port*>(item);
    if (port) {
      return port;
    }
  }
  return nullptr;
}

void Scene::changeActiveTool(const QPointF nowScenePos) {
  if (!Editor::getInstance()->activeTool()->isUsing()) {
    if (existPort(nowScenePos)) {
      Editor::getInstance()->changeActiveTool(TOOL_CONNECTION_CREATE);
      QGuiApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
    } else {
      Editor::getInstance()->changeActiveTool(TOOL_NODE_CREATE);
      QGuiApplication::restoreOverrideCursor();
    }
  }
}

Port* Scene::findStartPort(QPointF scenePos) {
  QList<QGraphicsItem*> pressedItems = items(scenePos);

  Port* port = nullptr;
  foreach (QGraphicsItem* item, pressedItems) {
    port = dynamic_cast<Port*>(item);
    if (port) {
      if (Output == port->io()) {
        return port;
      }
    }
  }
  return nullptr;
}

Port* Scene::findEndPort(QPointF scenePos) {
  QList<QGraphicsItem*> pressedItems = items(scenePos);

  Port* port = nullptr;
  foreach (QGraphicsItem* item, pressedItems) {
    port = dynamic_cast<Port*>(item);
    if (port) {
      if (Input == port->io()) {
        return port;
      }
    }
  }
  return nullptr;
}

Connection* Scene::findConnection(QPointF scenePos) {
  QList<QGraphicsItem*> pressedItems = items(scenePos);

  Connection* connection = nullptr;
  foreach (QGraphicsItem* item, pressedItems) {
    connection = dynamic_cast<Connection*>(item);
    if (connection && (m_tmpConnection != connection)) {
      return connection;
    }
  }
  return nullptr;
}

QList<AbstractNode*> Scene::findNodes(QPointF scenePos) {
  QList<AbstractNode*> nodes;
  foreach (QGraphicsItem* item, items(scenePos)) {
    AbstractNode* node = dynamic_cast<AbstractNode*>(item);
    if (node) {
      nodes << node;
    }
  }

  return nodes;
}

AbstractNode* Scene::findNode(const QString& nodeName) {
  foreach (AbstractNode* node, m_nodes) {
    if (nodeName == node->name()) {
      return node;
    }
  }
  return nullptr;
}

bool Scene::existNode(QPointF scenePos) {
  if (0 < findNodes(scenePos).count()) {
    return true;
  }
  return false;
}

bool Scene::existPort(QPointF scenePos) {
  if (findPort(scenePos)) {
    return true;
  }
  return false;
}

void Scene::showConnector(QPointF scenePos) {
  if (!m_tmpConnector) {
    m_tmpConnector = new Connector();
    addItem(m_tmpConnector);
  }
  m_tmpConnector->setPos(scenePos);
}

QList<AbstractNode*> Scene::nodes() const { return m_nodes; }

QList<AbstractNode*> Scene::nearTopNodes(const qreal top) const
{
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, m_nodes) {
    if(between(top, (node->top() - TORELANCE), (node->top() + TORELANCE))){
      nearNodes.append(node);
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearTopNodes(const qreal top, const SelectedFilter filter) const
{
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, nearTopNodes(top)) {
    if(filter == node->isSelected()){
      nearNodes << node;
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearBottomNodes(const qreal bottom) const
{
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, m_nodes) {
    if(between(bottom, (node->bottom() - TORELANCE), (node->bottom() + TORELANCE))){
      nearNodes.append(node);
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearBottomNodes(const qreal bottom, const Scene::SelectedFilter filter) const
{
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, nearBottomNodes(bottom)) {
    if(filter == node->isSelected()){
      nearNodes << node;
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearRightNodes(const qreal right) const
{
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, m_nodes) {
    if(between(right, (node->right() - TORELANCE), (node->right() + TORELANCE))){
      nearNodes.append(node);
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearRightNodes(const qreal right, const Scene::SelectedFilter filter) const
{
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, nearRightNodes(right)) {
    if(filter == node->isSelected()){
      nearNodes << node;
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearLeftNodes(const qreal left) const
{
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, m_nodes) {
    if(between(left, (node->left() - TORELANCE), (node->left() + TORELANCE))){
      nearNodes.append(node);
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearLeftNodes(const qreal left, const Scene::SelectedFilter filter) const
{
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, nearLeftNodes(left)) {
    if(filter == node->isSelected()){
      nearNodes << node;
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::selectedNodes() const
{
  QList<AbstractNode*> selectNodes;
  foreach (AbstractNode* node, m_nodes) {
    if(node->isSelected()){
      selectNodes << node;
    }
  }
  return selectNodes;
}

void Scene::addNode(AbstractNode* node, QPointF scenePos) {
  node->setPos(scenePos);
  m_nodes << node;
  addItem(node);
}

void Scene::removeNode(AbstractNode* node) {
  foreach (Port* removeNodePort, node->ports()) {
    foreach (Connection* connection, removeNodePort->connections()) { removeConnection(connection); }
  }
  m_nodes.removeOne(node);
  removeItem(node);
  delete node;
  node = nullptr;
}

QList<Connection*> Scene::connections() const { return m_connections; }

void Scene::addConnection(Connection* connection, Port* startPort) {
  connection->setStartPort(startPort);
  connection->setStartPos(startPort->centerScenePos());
  startPort->addConnection(connection);

  connection->setEndPos(startPort->centerScenePos());

  m_connections.append(connection);
  addItem(connection);
}

void Scene::addConnection(Connection* connection, Port* startPort, Port* endPort) {
  connection->setStartPort(startPort);
  connection->setStartPos(startPort->centerScenePos());
  startPort->addConnection(connection);

  connection->setEndPort(endPort);
  connection->setEndPos(endPort->centerScenePos());
  endPort->addConnection(connection);

  m_connections.append(connection);
  addItem(connection);
}

void Scene::addConnection(const QString& startNodeName, int32_t startPortNumber, const QString& endNodeName, int32_t endPortNumber) {
  AbstractNode* startNode = findNode(startNodeName);
  AbstractNode* endNode = findNode(endNodeName);

  Port* startPort = startNode->port(startPortNumber);
  Port* endPort = endNode->port(endPortNumber);

  Connection* connection = new Connection();

  addConnection(connection, startPort, endPort);

  connection->updatePath();
}

void Scene::removeConnection(Connection* connection) {
  // when connection is tmp connection,
  // start or end port maybe become null pointer
  Port* startPort = connection->startPort();
  if (startPort) {
    startPort->removeConnection(connection);
    connection->removeStartPort();
  }

  Port* endPort = connection->endPort();
  if (endPort) {
    endPort->removeConnection(connection);
    connection->removeEndPort();
  }

  m_connections.removeOne(connection);
  delete connection;
  connection = nullptr;
}

void Scene::addGuideLine(GuideLine* guideLine)
{
  addItem(guideLine);
  m_guideLines << guideLine;
}

void Scene::clearGuideLine()
{
  foreach (QGraphicsLineItem* guideLine, m_guideLines) {
    removeItem(guideLine);
  }
  qDeleteAll(m_guideLines);
  m_guideLines.clear();
}
