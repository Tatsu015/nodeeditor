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
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "ElbowConnection.h"
#include "PolylineConnection.h"

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

  if (isOnConnectablePort(scene, event)) {
    m_tmpConnection->changeConnectionStyle(AbstractConnection::Connectable);
    m_tmpConnection->redraw(m_startPort, event->scenePos());
    return;
  }

  if (isOnConnecttableConnection(scene, event)) {
    m_tmpConnection->changeConnectionStyle(AbstractConnection::Connectable);
    m_tmpConnection->redraw(m_startPort, event->scenePos());
    return;
  }

  if (isOnNode(scene, event)) {
    m_tmpConnection->changeConnectionStyle(AbstractConnection::Connectable);
    m_tmpConnection->redraw(m_startPort, event->scenePos());
    return;
  }
  m_tmpConnection->changeConnectionStyle(AbstractConnection::Connecting);
  m_tmpConnection->redraw(m_startPort, event->scenePos());
}

void ConnectionCreateTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (!m_startPort) {
    return;
  }

  if (isOnConnectablePort(scene, event)) {
    Port* endPort = scene->findPort(event->scenePos());
    decideConnectToPort(scene, endPort, m_tmpConnection->vertexes());
    scene->removeConnection(m_tmpConnection);
    m_startPort->removeConnection(m_tmpConnection);
    reset();
    return;
  }

  if (isOnConnecttableConnection(scene, event)) {
    AbstractConnection* dstConnection = scene->findConnection(event->scenePos(), m_tmpConnection);
    decideConnectToConnector(scene, event->scenePos(), dstConnection, m_tmpConnection->vertexes());
    scene->removeConnection(m_tmpConnection);
    m_startPort->removeConnection(m_tmpConnection);
    reset();
    return;
  }

  if (isOnNode(scene, event)) {
    AbstractNode* node = scene->findNodes(event->scenePos()).at(0);
    Port* endPort;
    IO io = m_startPort->io();
    if (Input == io) {
      endPort = node->nearestOutputPort(event->scenePos());
    } else {
      endPort = node->nearestInputPort(event->scenePos());
    }
    decideConnectToPort(scene, endPort, m_tmpConnection->vertexes());
    scene->removeConnection(m_tmpConnection);
    m_startPort->removeConnection(m_tmpConnection);
    cancel();
    reset();
    return;
  }

  if (CONNECTION_POLYLINE == m_tmpConnection->connectionType()) {
    m_tmpConnection->addVertex(event->scenePos());
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
    Editor::getInstance()->addCommand(new NodeRemoveCommand(scene, activeSheet, scene->selectedNodes()));
  }
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

bool ConnectionCreateTool::isOnConnectablePort(Scene* scene, QGraphicsSceneMouseEvent* event) const {
  Port* endPort = scene->findPort(event->scenePos());

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

bool ConnectionCreateTool::isOnNode(Scene* scene, QGraphicsSceneMouseEvent* event) const {
  QList<AbstractNode*> nodes = scene->findNodes(event->scenePos());
  if (0 >= nodes.count()) {
    return false;
  }
  return true;
}

bool ConnectionCreateTool::isOnConnecttableConnection(Scene* scene, QGraphicsSceneMouseEvent* event) const {
  QList<AbstractConnection*> connections = scene->findConnections(event->scenePos(), m_tmpConnection);
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
