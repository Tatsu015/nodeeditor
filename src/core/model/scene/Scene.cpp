#include "Scene.h"
#include "AbstractTool.h"
#include "AndNode.h"
#include "Common.h"
#include "Connection.h"
#include "ConnectionReconnectTool.h"
#include "Connector.h"
#include "Define.h"
#include "Editor.h"
#include "GuideLine.h"
#include "InNode.h"
#include "MenuManager.h"
#include "NodeEditTool.h"
#include "NodeFactory.h"
#include "NodeRemoveCommand.h"
#include "OutNode.h"
#include "Port.h"
#include "Project.h"
#include "SceneObserver.h"
#include "Sheet.h"
#include <QAction>
#include <QCursor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QMenu>

const static qreal TORELANCE = 5;

Scene::Scene(QObject* parent) : QGraphicsScene(-1000, -1000, 2000, 2000, parent), m_isControlPressed(false) {
  addLine(-5, -5, 5, 5, QPen(Qt::gray));
  addLine(-5, 5, 5, -5, QPen(Qt::gray));
}

Scene::~Scene() {
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
  QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
  Editor::getInstance()->activeTool()->mouseDoubleClickEvent(this, event);
  QGraphicsScene::mouseDoubleClickEvent(event);
}

void Scene::keyPressEvent(QKeyEvent* event) {
  Editor::getInstance()->activeTool()->keyPressEvent(this, event);
  if (Qt::Key_Control == event->key()) {
    m_isControlPressed = true;
  } else if (Qt::Key_A == event->key()) {
    if (m_isControlPressed) {
      foreach (AbstractNode* node, m_sheet->nodes()) { node->setSelected(true); }
    }
  } else if (Qt::Key_N == event->key()) {
    if (m_isControlPressed) {
      static int i;
      i = i % 3;
      ++i;
      Project* p = Editor::getInstance()->project();
      Sheet* s = p->sheet("sheet_" + QString::number(i));
      changeSheet(s);
    }
  } else if (Qt::Key_P == event->key()) {
    if (m_isControlPressed) {
      foreach (AbstractNode* node, m_sheet->nodes()) { addItem(node); }
      foreach (Connection* connection, m_sheet->connections()) { addItem(connection); }
      redraw();
    }
  }
  QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent* event) {
  Editor::getInstance()->activeTool()->keyReleaseEvent(this, event);
  if (Qt::Key_Control == event->key()) {
    m_isControlPressed = false;
  }
  QGraphicsScene::keyReleaseEvent(event);
}

void Scene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
  QMenu menu;
  // TODO...
  menu.addActions(MenuManager::getInstance()->contextMenuActions());
  menu.exec(event->screenPos());
  QGraphicsScene::contextMenuEvent(event);
}

Sheet* Scene::sheet() const {
  return m_sheet;
}

void Scene::setSheet(Sheet* sheet) {
  m_sheet = sheet;
}

void Scene::changeSheet(Sheet* sheet) {
  foreach (AbstractNode* node, m_sheet->nodes()) { removeNode(node); }
  foreach (Connection* connection, m_sheet->connections()) { removeConnection(connection); }
  m_sheet = sheet;
  foreach (AbstractNode* node, m_sheet->nodes()) { addNode(node); }
  foreach (Connection* connection, m_sheet->connections()) { addConnection(connection); }
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

void Scene::addSceneObserver(SceneObserver* sceneObserver) {
  m_sceneObservers << sceneObserver;
}

void Scene::takeOver(Scene* scene) {
  m_sceneObservers = scene->m_sceneObservers;
}

void Scene::changeActiveTool(const QPointF nowScenePos) {
  if (!Editor::getInstance()->activeTool()->isUsing()) {
    Port* port = findPort(nowScenePos);
    if (port) {
      if (port->canConnect()) {
        Editor::getInstance()->changeActiveTool(TOOL_CONNECTION_CREATE);
        QGuiApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
      } else {
        Editor::getInstance()->changeActiveTool(TOOL_CONNECTION_RECONNECT);
        QGuiApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
      }
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

Connection* Scene::findConnection(const QPointF scenePos, Connection* tmponnection) {
  QList<QGraphicsItem*> pressedItems = items(scenePos);

  Connection* connection = nullptr;
  foreach (QGraphicsItem* item, pressedItems) {
    connection = dynamic_cast<Connection*>(item);
    // remove creating connection from target
    if (connection != tmponnection) {
      return connection;
    }
  }
  return nullptr;
}

Connection* Scene::findConnection(const QString connectionName) {
  foreach (Connection* connection, m_sheet->connections()) {
    if (connectionName == connection->name()) {
      return connection;
    }
  }
  return nullptr;
}

QList<Connection*> Scene::findConnections(const QPointF scenePos, Connection* tmponnection) {
  QList<QGraphicsItem*> pressedItems = items(scenePos);
  QList<Connection*> connections;
  foreach (QGraphicsItem* item, pressedItems) {
    Connection* connection = dynamic_cast<Connection*>(item);
    // remove except connection and tmp connection from target
    if ((connection) && (connection != tmponnection)) {
      connections << connection;
    }
  }
  return connections;
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
  foreach (AbstractNode* node, m_sheet->nodes()) {
    if (nodeName == node->name()) {
      return node;
    }
  }
  return nullptr;
}

bool Scene::existPort(QPointF scenePos) {
  if (findPort(scenePos)) {
    return true;
  }
  return false;
}

// TODO will delete
// QList<AbstractNode*> Scene::nodes() const {
//  return m_sheet->nodes();
//}

QList<AbstractNode*> Scene::nearTopNodes(const qreal top) const {
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, m_sheet->nodes()) {
    if (between(top, (node->top() - TORELANCE), (node->top() + TORELANCE))) {
      nearNodes.append(node);
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearTopNodes(const qreal top, const SelectedFilter filter) const {
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, nearTopNodes(top)) {
    if (filter == node->isSelected()) {
      nearNodes << node;
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearBottomNodes(const qreal bottom) const {
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, m_sheet->nodes()) {
    if (between(bottom, (node->bottom() - TORELANCE), (node->bottom() + TORELANCE))) {
      nearNodes.append(node);
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearBottomNodes(const qreal bottom, const Scene::SelectedFilter filter) const {
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, nearBottomNodes(bottom)) {
    if (filter == node->isSelected()) {
      nearNodes << node;
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearRightNodes(const qreal right) const {
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, m_sheet->nodes()) {
    if (between(right, (node->right() - TORELANCE), (node->right() + TORELANCE))) {
      nearNodes.append(node);
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearRightNodes(const qreal right, const Scene::SelectedFilter filter) const {
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, nearRightNodes(right)) {
    if (filter == node->isSelected()) {
      nearNodes << node;
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearLeftNodes(const qreal left) const {
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, m_sheet->nodes()) {
    if (between(left, (node->left() - TORELANCE), (node->left() + TORELANCE))) {
      nearNodes.append(node);
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::nearLeftNodes(const qreal left, const Scene::SelectedFilter filter) const {
  QList<AbstractNode*> nearNodes;
  foreach (AbstractNode* node, nearLeftNodes(left)) {
    if (filter == node->isSelected()) {
      nearNodes << node;
    }
  }
  return nearNodes;
}

QList<AbstractNode*> Scene::selectedNodes() const {
  QList<AbstractNode*> selectNodes;
  foreach (AbstractNode* node, m_sheet->nodes()) {
    if (node->isSelected()) {
      selectNodes << node;
    }
  }
  return selectNodes;
}

void Scene::addNode(AbstractNode* node) {
  addItem(node);
  notifyAdd(node);
}

void Scene::removeNode(AbstractNode* node) {
  removeItem(node);
  notifyRemove(node);
}

void Scene::addConnection(Connection* connection) {
  addItem(connection);
  redraw();
}

void Scene::removeConnection(Connection* connection) {
  removeItem(connection);
}

void Scene::addGuideLine(GuideLine* guideLine) {
  addItem(guideLine);
  m_guideLines << guideLine;
}

void Scene::clearGuideLine() {
  foreach (QGraphicsLineItem* guideLine, m_guideLines) { removeItem(guideLine); }
  qDeleteAll(m_guideLines);
  m_guideLines.clear();
}

void Scene::notifyAdd(AbstractNode* node) {
  foreach (SceneObserver* sceneObserver, m_sceneObservers) { sceneObserver->addNode(node); }
}

void Scene::notifyRemove(AbstractNode* node) {
  foreach (SceneObserver* sceneObserver, m_sceneObservers) { sceneObserver->removeNode(node); }
}

void Scene::redraw() {
  foreach (Connection* connection, m_sheet->connections()) { connection->redraw(); }
}
