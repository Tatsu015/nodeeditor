#include "ConnectionCreateTool.h"
#include "AbstractNode.h"
#include "ConnectToConnectorCommand.h"
#include "ConnectToPortCommand.h"
#include "Connection.h"
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

ConnectionCreateTool::ConnectionCreateTool() : AbstractTool(TOOL_CONNECTION_CREATE) {
  m_tmpConnection = new Connection();
}

ConnectionCreateTool::~ConnectionCreateTool() {
}

void ConnectionCreateTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  m_startPort = scene->findPort(event->scenePos());
  if (!m_startPort) {
    return;
  }

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
    m_tmpConnection->changeConnectionStyle(Connection::Connectable);
    m_tmpConnection->redraw(m_startPort, event->scenePos());
    return;
  }

  if (isOnConnecttableConnection(scene, event)) {
    m_tmpConnection->changeConnectionStyle(Connection::Connectable);
    m_tmpConnection->redraw(m_startPort, event->scenePos());
    return;
  }

  // TODO
  //  if (isOnNode(scene, event)) {
  //    AbstractNode* node = scene->findNodes(event->scenePos()).at(0);
  //    Port* endPort = node->nearestPort(event->scenePos());
  //    m_tmpConnection->changePenStyle(TmpConnection::Connectable);
  //    m_tmpConnection->redraw(m_startPort, event->scenePos());
  //    return;
  //  }
  m_tmpConnection->changeConnectionStyle(Connection::Connecting);
  m_tmpConnection->redraw(m_startPort, event->scenePos());
}

void ConnectionCreateTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (!m_startPort) {
    return;
  }

  scene->removeConnection(m_tmpConnection);
  if (isOnConnectablePort(scene, event)) {
    Port* endPort = scene->findPort(event->scenePos());
    decideConnectToPort(scene, endPort);
    reset();
    return;
  }

  if (isOnConnecttableConnection(scene, event)) {
    Connection* dstConnection = scene->findConnection(event->scenePos(), m_tmpConnection);
    decideConnectToConnector(scene, event->scenePos(), dstConnection);
    reset();
    return;
  }

  // TODO
  //  if (isOnNode(scene, event)) {
  //    AbstractNode* node = scene->findNodes(event->scenePos()).at(0);
  //    Port* endPort = node->nearestPort(event->scenePos());
  //    decideConnectToPort(scene, endPort);
  //  }

  cancel();
  reset();
}

void ConnectionCreateTool::keyPressEvent(Scene* scene, QKeyEvent* event) {
  if (Qt::Key_Delete == event->key()) {
    Sheet* activeSheet = scene->sheet();
    Editor::getInstance()->addCommand(new NodeRemoveCommand(scene, activeSheet, scene->selectedNodes()));
  }
}

void ConnectionCreateTool::decideConnectToPort(Scene* scene, Port* endPort) {
  Sheet* activeSheet = scene->sheet();
  Connection* connection = ConnectionFactory::getInstance()->createConnection(activeSheet, CONNECTION);
  ConnectToPortCommand* command = new ConnectToPortCommand(scene, activeSheet, connection, m_startPort, endPort);
  Editor::getInstance()->addCommand(command);
}

void ConnectionCreateTool::decideConnectToConnector(Scene* scene, QPointF mouseReleaseScenePos,
                                                    Connection* dstConnection) {
  Sheet* activeSheet = scene->sheet();
  Connection* connection = ConnectionFactory::getInstance()->createConnection(activeSheet, CONNECTION);
  Connector* connector = ConnectorFactory::getInstance()->createConnector(CONNECTOR, connection);
  connector->setPos(dstConnection->closeCenter(mouseReleaseScenePos) + connector->centerOffset());

  QPointF connectorPosDiff = connector->centerScenePos() - dstConnection->startPos();
  QPointF connectionPosDiff = dstConnection->endPos() - dstConnection->startPos();
  qreal xPosRate = connectorPosDiff.x() / connectionPosDiff.x();
  qreal yPosRate = connectorPosDiff.y() / connectionPosDiff.y();
  connector->setXPosRate(xPosRate);
  connector->setYPosRate(yPosRate);

  ConnectToConnectorCommand* command =
      new ConnectToConnectorCommand(scene, scene->sheet(), connection, m_startPort, connector, dstConnection);
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
  QList<Connection*> connections = scene->findConnections(event->scenePos(), m_tmpConnection);
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
