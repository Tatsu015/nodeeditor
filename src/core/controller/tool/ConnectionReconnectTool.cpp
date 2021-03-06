#include "ConnectionReconnectTool.h"
#include "AbstractConnection.h"
#include "AbstractNode.h"
#include "ConnectToConnectorCommand.h"
#include "ConnectionFactory.h"
#include "ConnectorFactory.h"
#include "Define.h"
#include "EdgeHandle.h"
#include "Editor.h"
#include "GuideLine.h"
#include "NodeAddCommand.h"
#include "NodeFactory.h"
#include "NodeFactory.h"
#include "NodeMoveCommand.h"
#include "NodeRemoveCommand.h"
#include "Port.h"
#include "Project.h"
#include "ReconnectToPortCommand.h"
#include "Scene.h"
#include "Sheet.h"
#include <QAction>
#include <QCursor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>

const static qreal GUIDELINE_DRAWOVER_SIZE = 10;

ConnectionReconnectTool::ConnectionReconnectTool() : AbstractTool(TOOL_CONNECTION_RECONNECT) {
}

ConnectionReconnectTool::~ConnectionReconnectTool() {
}

void ConnectionReconnectTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  EdgeHandle* edgeHandle = scene->findEdgeHandle(event->scenePos());
  AbstractConnection* connection = edgeHandle->connection();
  if (Start == edgeHandle->edge()) {
    m_lastEndPort = connection->startPort();
  } else {
    m_lastEndPort = connection->endPort();
  }

  if (!m_lastEndPort) {
    return;
  }

  m_connection = m_lastEndPort->connections().first();
  m_fixedPort = m_connection->oppositeSidePort(m_lastEndPort);
  if (m_lastEndPort == m_connection->endPort()) {
    m_isMoveStartPort = false;
    m_connection->removeEndPort();
  } else {
    m_isMoveStartPort = true;
    m_connection->removeStartPort();
  }
  m_lastEndPort->removeConnection(m_connection);

  m_isUsing = true;
  m_isNodeSelectable = false;
  m_isReconnecting = true;
}

void ConnectionReconnectTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  if (!m_fixedPort) {
    return;
  }

  if (isOnConnectablePort(scene, event)) {
    m_connection->changeConnectionStyle(AbstractConnection::Connectable);
    return;
  }

  if (isOnConnecttableConnection(scene, event)) {
    m_connection->changeConnectionStyle(AbstractConnection::Connectable);
    return;
  }

  m_connection->changeConnectionStyle(AbstractConnection::Connecting);
  m_connection->redraw(m_fixedPort, event->scenePos());
}

void ConnectionReconnectTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (!m_fixedPort) {
    return;
  }

  m_connection->changeConnectionStyle(AbstractConnection::Connected);

  Port* endPort = scene->findPort(event->scenePos());
  if (m_lastEndPort == endPort) {
    cancel();
    reset();
    return;
  }

  if (isOnConnectablePort(scene, event)) {
    Port* endPort = scene->findPort(event->scenePos());
    decideConnectToPort(scene, m_lastEndPort, endPort);
    reset();
    return;
  }

  if (isOnConnecttableConnection(scene, event)) {
    AbstractConnection* dstConnection = scene->findConnection(event->scenePos(), m_connection);
    decideConnectToConnector(scene, event->scenePos(), dstConnection);
    reset();
    return;
  }

  cancel();
  reset();
}

bool ConnectionReconnectTool::isActivatable(Scene* scene, QGraphicsSceneMouseEvent* event) {
  EdgeHandle* edgeHandle = scene->findEdgeHandle(event->scenePos(), false);
  if (edgeHandle) {
    QGuiApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
    return true;
  }
  return false;
}

void ConnectionReconnectTool::decideConnectToPort(Scene* scene, Port* lastEndPort, Port* targetEndPort) {
  Sheet* activeSheet = scene->sheet();
  ReconnectToPortCommand* command =
      new ReconnectToPortCommand(scene, activeSheet, m_connection, lastEndPort, targetEndPort, m_isMoveStartPort);
  Editor::getInstance()->addCommand(command);

  m_fixedPort = nullptr;
}

void ConnectionReconnectTool::decideConnectToConnector(Scene* scene, QPointF mouseReleaseScenePos,
                                                       AbstractConnection* dstConnection) {
  Sheet* activeSheet = scene->sheet();
  Connector* connector = ConnectorFactory::getInstance()->createConnector(CONNECTOR, m_connection);
  connector->setPos(dstConnection->closeCenter(mouseReleaseScenePos) + connector->centerOffset());

  QPointF connectorPosDiff = connector->centerScenePos() - dstConnection->startPos();
  QPointF connectionPosDiff = dstConnection->endPos() - dstConnection->startPos();
  qreal xPosRate = connectorPosDiff.x() / connectionPosDiff.x();
  qreal yPosRate = connectorPosDiff.y() / connectionPosDiff.y();
  connector->setXPosRate(xPosRate);
  connector->setYPosRate(yPosRate);

  ConnectToConnectorCommand* command = new ConnectToConnectorCommand(scene, activeSheet, m_connection, m_fixedPort,
                                                                     connector, dstConnection, QList<QPointF>());
  Editor::getInstance()->addCommand(command);

  m_fixedPort = nullptr;
}

bool ConnectionReconnectTool::isOnConnectablePort(Scene* scene, QGraphicsSceneMouseEvent* event) const {
  Port* endPort = scene->findPort(event->scenePos());

  if (!endPort) {
    return false;
  }

  if (m_fixedPort == endPort) {
    return false;
  }
  if (m_fixedPort->parentNode() == endPort->parentNode()) {
    return false;
  }
  if (m_fixedPort->io() == endPort->io()) {
    return false;
  }
  return true;
}

bool ConnectionReconnectTool::isOnNode(Scene* scene, QGraphicsSceneMouseEvent* event) const {
  QList<AbstractNode*> nodes = scene->findNodes(event->scenePos());
  if (0 >= nodes.count()) {
    return false;
  }
  return true;
}

bool ConnectionReconnectTool::isOnConnecttableConnection(Scene* scene, QGraphicsSceneMouseEvent* event) const {
  QList<AbstractConnection*> connections = scene->findConnections(event->scenePos(), m_connection);
  // now connection creating, so m_tmpConnection always contains in connections.
  // but this function need to find connect to connection, so remove m_tmpConnection.

  if (0 == connections.count()) {
    return false;
  }
  return true;
}

void ConnectionReconnectTool::cancel() {
  if (m_isMoveStartPort) {
    m_connection->setStartPort(m_lastEndPort);
    m_lastEndPort->addConnection(m_connection);
  } else {
    m_connection->setEndPort(m_lastEndPort);
    m_lastEndPort->addConnection(m_connection);
  }
}

void ConnectionReconnectTool::reset() {
  m_isUsing = false;
  m_isNodeSelectable = true;
  m_isReconnecting = false;

  m_disconnectedNode = nullptr;
  m_connection = nullptr;
  m_fixedPort = nullptr;
  m_lastEndPort = nullptr;
}
