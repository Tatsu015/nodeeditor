#include "ConnectionCreateTool.h"
#include "AbstractConnection.h"
#include "AbstractNode.h"
#include "ConnectToConnectorCommand.h"
#include "ConnectToPortCommand.h"
#include "ConnectionFactory.h"
#include "Connector.h"
#include "ConnectorFactory.h"
#include "Define.h"
#include "Editor.h"
#include "NodeRemoveCommand.h"
#include "PolylineConnection.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"
#include <QCursor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>

ConnectionCreateTool::ConnectionCreateTool() : AbstractTool(TOOL_CONNECTION_CREATE) {
  m_activeConnectionType = ConnectionFactory::getInstance()->connectionTypes().first();
}

ConnectionCreateTool::~ConnectionCreateTool() {
}

void ConnectionCreateTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (m_isUsing) {
    return;
  }
  m_startPort = scene->findPort(event->scenePos());
  if (!m_startPort) {
    return;
  }

  m_tmpConnection = ConnectionFactory::getInstance()->createConnection(m_activeConnectionType, "tmp", "tmp");
  m_tmpConnection->setStartPort(m_startPort);
  m_tmpConnection->setStartPos(m_startPort->endOfPortPos());
  m_tmpConnection->setEndPos(m_startPort->endOfPortPos());
  m_startPort->addConnection(m_tmpConnection);
  scene->addConnection(m_tmpConnection);

  m_isUsing = true;
  m_isNodeSelectable = false;
}

void ConnectionCreateTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  if (!m_startPort) {
    return;
  }

  QPointF endScenePos = modifieredEndScenePos(event);

  if (isOnConnectablePort(scene, endScenePos)) {
    m_tmpConnection->changeConnectionStyle(AbstractConnection::Connectable);
    m_tmpConnection->redraw(m_startPort, endScenePos);
    return;
  }

  if (isOnConnectableConnection(scene, endScenePos)) {
    m_tmpConnection->changeConnectionStyle(AbstractConnection::Connectable);
    m_tmpConnection->redraw(m_startPort, endScenePos);
    return;
  }

  if (isOnNode(scene, endScenePos)) {
    m_tmpConnection->changeConnectionStyle(AbstractConnection::Connectable);
    m_tmpConnection->redraw(m_startPort, endScenePos);
    return;
  }
  m_tmpConnection->changeConnectionStyle(AbstractConnection::Connecting);
  m_tmpConnection->redraw(m_startPort, endScenePos);
}

void ConnectionCreateTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (!m_startPort) {
    return;
  }

  QPointF endScenePos = modifieredEndScenePos(event);

  if (isOnConnectablePort(scene, endScenePos)) {
    Port* endPort = scene->findPort(endScenePos);
    decideConnectToPort(scene, endPort, m_tmpConnection->vertexes());
    scene->removeConnection(m_tmpConnection);
    m_startPort->removeConnection(m_tmpConnection);
    reset();
    return;
  }

  if (isOnConnectableConnection(scene, endScenePos)) {
    AbstractConnection* dstConnection = scene->findConnection(endScenePos, m_tmpConnection);
    decideConnectToConnector(scene, endScenePos, dstConnection, m_tmpConnection->vertexes());
    scene->removeConnection(m_tmpConnection);
    m_startPort->removeConnection(m_tmpConnection);
    reset();
    return;
  }

  if (isOnNode(scene, endScenePos)) {
    AbstractNode* node = scene->findNodes(endScenePos).at(0);
    Port* endPort;
    IO io = m_startPort->io();
    if (Input == io) {
      endPort = node->nearestOutputPort(endScenePos);
    } else {
      endPort = node->nearestInputPort(endScenePos);
    }
    decideConnectToPort(scene, endPort, m_tmpConnection->vertexes());
    scene->removeConnection(m_tmpConnection);
    m_startPort->removeConnection(m_tmpConnection);
    cancel();
    reset();
    return;
  }

  if (CONNECTION_POLYLINE == m_tmpConnection->connectionType()) {
    m_tmpConnection->addVertex(endScenePos);
    return;
  }

  scene->removeConnection(m_tmpConnection);
  m_startPort->removeConnection(m_tmpConnection);
  cancel();
  reset();
}

void ConnectionCreateTool::keyPressEvent(Scene* scene, QKeyEvent* event) {
  if (Qt::Key_Delete == event->key()) {
    Sheet* activeSheet = scene->sheet();
    Editor::getInstance()->addCommand(
        new NodeRemoveCommand(scene, activeSheet, scene->selectedNodes(), scene->selectedConnections()));
  }
}

bool ConnectionCreateTool::isActivatable(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Port* port = scene->findPort(event->scenePos(), false);
  if (port) {
    if (port->canConnect()) {
      QGuiApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
      return true;
    }
  }
  return false;
}

void ConnectionCreateTool::setActiveConnectionType(const QString& activeConnectionType) {
  m_activeConnectionType = activeConnectionType;
}

void ConnectionCreateTool::decideConnectToPort(Scene* scene, Port* endPort, QList<QPointF> vertexes) {
  Sheet* activeSheet = scene->sheet();
  AbstractConnection* connection =
      ConnectionFactory::getInstance()->createConnection(activeSheet, m_activeConnectionType);
  ConnectToPortCommand* command =
      new ConnectToPortCommand(scene, activeSheet, connection, m_startPort, endPort, vertexes);
  Editor::getInstance()->addCommand(command);
}

void ConnectionCreateTool::decideConnectToConnector(Scene* scene, QPointF mouseReleaseScenePos,
                                                    AbstractConnection* dstConnection, QList<QPointF> vertexes) {
  Sheet* activeSheet = scene->sheet();
  AbstractConnection* connection =
      ConnectionFactory::getInstance()->createConnection(activeSheet, m_activeConnectionType);
  Connector* connector = ConnectorFactory::getInstance()->createConnector(CONNECTOR, connection);
  connector->setPos(dstConnection->closeCenter(mouseReleaseScenePos) + connector->centerOffset());

  QPointF connectorPosDiff = connector->centerScenePos() - dstConnection->startPos();
  QPointF connectionPosDiff = dstConnection->endPos() - dstConnection->startPos();
  qreal xPosRate = connectorPosDiff.x() / connectionPosDiff.x();
  qreal yPosRate = connectorPosDiff.y() / connectionPosDiff.y();
  connector->setXPosRate(xPosRate);
  connector->setYPosRate(yPosRate);

  ConnectToConnectorCommand* command =
      new ConnectToConnectorCommand(scene, scene->sheet(), connection, m_startPort, connector, dstConnection, vertexes);
  Editor::getInstance()->addCommand(command);
}

bool ConnectionCreateTool::isOnConnectablePort(Scene* scene, const QPointF scenePos) const {
  Port* endPort = scene->findPort(scenePos);

  if (!endPort) {
    return false;
  }
  if (m_startPort == endPort) {
    return false;
  }
  if (m_startPort->parentNode() == endPort->parentNode()) {
    return false;
  }
  if (m_startPort->io() == endPort->io()) {
    return false;
  }
  return true;
}

bool ConnectionCreateTool::isOnNode(Scene* scene, const QPointF scenePos) const {
  QList<AbstractNode*> nodes = scene->findNodes(scenePos);
  if (0 >= nodes.count()) {
    return false;
  }
  return true;
}

bool ConnectionCreateTool::isOnConnectableConnection(Scene* scene, const QPointF scenePos) const {
  QList<AbstractConnection*> connections = scene->findConnections(scenePos, m_tmpConnection);
  // now connection creating, so m_tmpConnection always contains in connections.
  // but this function need to find connect to connection, so remove m_tmpConnection.
  connections.removeOne(m_tmpConnection);

  if (0 == connections.count()) {
    return false;
  }
  return true;
}

void ConnectionCreateTool::cancel() {
  m_startPort->removeConnection(m_tmpConnection);
}

void ConnectionCreateTool::reset() {
  m_isUsing = false;
  m_isNodeSelectable = true;

  m_startPort = nullptr;
}

QPointF ConnectionCreateTool::modifieredEndScenePos(QGraphicsSceneMouseEvent* event) {
  if (Qt::ShiftModifier != event->modifiers()) {
    return event->scenePos();
  } else {
    QPointF lastPos;
    if (m_tmpConnection->vertexes().isEmpty()) {
      lastPos = m_startPort->endOfPortPos();
    } else {
      lastPos = m_tmpConnection->vertexes().last();
    }
    QLineF direction(lastPos, event->scenePos());
    qreal angle = direction.angle();
    if ((45 < angle) && (angle <= 135)) {
      return QPointF(lastPos.x(), event->scenePos().y());
    } else if ((135 < angle) && (angle <= 225)) {
      return QPointF(event->scenePos().x(), lastPos.y());
    } else if ((225 < angle) && (angle <= 315)) {
      return QPointF(lastPos.x(), event->scenePos().y());
    } else {
      return QPointF(event->scenePos().x(), lastPos.y());
    }
  }
  return QPointF();
}
