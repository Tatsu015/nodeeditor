#include "Scene.h"
#include "AbstractConnection.h"
#include "AbstractTool.h"
#include "AndNode.h"
#include "Common.h"
#include "ConnectionCreateTool.h"
#include "ConnectionReconnectTool.h"
#include "Connector.h"
#include "ContextMenuManager.h"
#include "Define.h"
#include "Editor.h"
#include "FunctionBlockNode.h"
#include "GuideLine.h"
#include "NodeEditTool.h"
#include "NodeRemoveCommand.h"
#include "Port.h"
#include "Project.h"
#include "SceneObserver.h"
#include "Sheet.h"
#include "SheetJumpTool.h"
#include <QAction>
#include <QCursor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QMenu>

const static qreal TORELANCE = 5;
const static QRectF SCENE_RECT(0, 0, 300, 400);

Scene::Scene(QObject* parent) : QGraphicsScene(SCENE_RECT, parent) {
  const static QString DEFAULT_TEXT = "    How to Open Project\n"
                                      "---------------------------\n"
                                      "    ・ File -> Open\n"
                                      "    ・ File -> New\n"
                                      "    ・ Drag and Drop *." +
                                      APP_EXTENSION + " file";
  m_defaultText = new QGraphicsTextItem(DEFAULT_TEXT);
  m_defaultText->setDefaultTextColor(QColor(Qt::gray));
  showDefaultText();
}

Scene::~Scene() {
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  changeActiveTool(event);
  Editor::getInstance()->activeTool()->mousePressEvent(this, event);
  QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
  changeActiveTool(event);
  Editor::getInstance()->activeTool()->mouseMoveEvent(this, event);
  QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
  Editor::getInstance()->activeTool()->mouseReleaseEvent(this, event);
  if (!Editor::getInstance()->activeTool()->isUsing()) {
    Editor::getInstance()->changeDefaultTool();
  }
  QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
  Editor::getInstance()->activeTool()->mouseDoubleClickEvent(this, event);
  QGraphicsScene::mouseDoubleClickEvent(event);
}

void Scene::keyPressEvent(QKeyEvent* event) {
  Editor::getInstance()->activeTool()->keyPressEvent(this, event);
  if ((Qt::Key_A == event->key()) && Qt::ControlModifier == event->modifiers()) {
    foreach (AbstractNode* node, m_sheet->nodes()) { node->setSelected(true); }
  }
  if (Qt::Key_Control == event->key()) {
    // TODO
    //    FunctionBlockNode* functionBlockNode = dynamic_cast<FunctionBlockNode*>(findNode(mousepo));
    //    if (functionBlockNode && (Qt::ControlModifier == event->modifiers())) {
    //      Editor::getInstance()->changeActiveTool(TOOL_SHEET_JUMP);
    //      QGuiApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
    //    }
  }
  QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent* event) {
  Editor::getInstance()->activeTool()->keyReleaseEvent(this, event);
  QGraphicsScene::keyReleaseEvent(event);
}

void Scene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event) {
  QMenu* menu = ContextMenuManager::getInstance()->contextMenu(event);
  menu->exec(event->screenPos());
  QGraphicsScene::contextMenuEvent(event);
}

Sheet* Scene::sheet() const {
  return m_sheet;
}

void Scene::setSheet(Sheet* sheet) {
  hideDefaultText();
  m_sheet = sheet;
}

void Scene::changeSheet(Sheet* sheet) {
  removeSheet();
  hideDefaultText();
  m_sheet = sheet;
  foreach (AbstractNode* node, m_sheet->nodes()) { addNode(node); }
  foreach (AbstractConnection* connection, m_sheet->connections()) { addConnection(connection); }
}

void Scene::removeSheet() {
  // when first call this method, m_sheet is nullptr.
  if (m_sheet) {
    foreach (AbstractNode* node, m_sheet->nodes()) { removeNode(node); }
    foreach (AbstractConnection* connection, m_sheet->connections()) { removeConnection(connection); }
  }
  showDefaultText();
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

void Scene::changeActiveTool(QGraphicsSceneMouseEvent* event) {
  if (!Editor::getInstance()->activeTool()->isUsing()) {
    Port* port = findPort(event->scenePos());
    FunctionBlockNode* functionBlockNode = dynamic_cast<FunctionBlockNode*>(findNode(event->scenePos()));
    if (port) {
      if (port->canConnect()) {
        Editor::getInstance()->changeActiveTool(TOOL_CONNECTION_CREATE);
        QGuiApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
      } else {
        Editor::getInstance()->changeActiveTool(TOOL_CONNECTION_RECONNECT);
        QGuiApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
      }
    } else if (functionBlockNode) {
      if (Qt::ControlModifier == event->modifiers()) {
        Editor::getInstance()->changeActiveTool(TOOL_SHEET_JUMP);
        QGuiApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
      } else {
        Editor::getInstance()->changeActiveTool(TOOL_NODE_EDIT);
        QGuiApplication::restoreOverrideCursor();
      }
    } else {
      Editor::getInstance()->changeActiveTool(TOOL_NODE_EDIT);
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

AbstractConnection* Scene::findConnection(const QPointF scenePos, AbstractConnection* tmponnection) {
  QList<QGraphicsItem*> pressedItems = items(scenePos);

  AbstractConnection* connection = nullptr;
  foreach (QGraphicsItem* item, pressedItems) {
    connection = dynamic_cast<AbstractConnection*>(item);
    // remove creating connection from target
    if (connection != tmponnection) {
      return connection;
    }
  }
  return nullptr;
}

AbstractConnection* Scene::findConnection(const QString connectionName) {
  foreach (AbstractConnection* connection, m_sheet->connections()) {
    if (connectionName == connection->name()) {
      return connection;
    }
  }
  return nullptr;
}

QList<AbstractConnection*> Scene::findConnections(const QPointF scenePos, AbstractConnection* tmponnection) {
  QList<QGraphicsItem*> pressedItems = items(scenePos);
  QList<AbstractConnection*> connections;
  foreach (QGraphicsItem* item, pressedItems) {
    AbstractConnection* connection = dynamic_cast<AbstractConnection*>(item);
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

AbstractNode* Scene::findNode(QPointF scenePos) {
  QList<AbstractNode*> nodes = findNodes(scenePos);
  if (0 >= nodes.count()) {
    return nullptr;
  }
  return nodes.first();
}

bool Scene::existPort(QPointF scenePos) {
  if (findPort(scenePos)) {
    return true;
  }
  return false;
}

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

void Scene::addConnection(AbstractConnection* connection) {
  addItem(connection);
  redraw();
}

void Scene::removeConnection(AbstractConnection* connection) {
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

void Scene::showDefaultText() {
  m_defaultText->setPos(sceneRect().center() - m_defaultText->boundingRect().center());
  addItem(m_defaultText);
}

void Scene::hideDefaultText() {
  removeItem(m_defaultText);
}

void Scene::redraw() {
  foreach (AbstractConnection* connection, m_sheet->connections()) { connection->redraw(); }
}
