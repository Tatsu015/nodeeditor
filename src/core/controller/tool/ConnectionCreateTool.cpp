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
#include "TmpConnection.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

ConnectionCreateTool::ConnectionCreateTool() : AbstractTool(TOOL_CONNECTION_CREATE) {
  m_tmpConnection = new TmpConnection();
  m_tmpConnector = new Connector();
}

ConnectionCreateTool::~ConnectionCreateTool() {
}

void ConnectionCreateTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  m_startPort = scene->findPort(event->scenePos());
  if (!m_startPort) {
    return;
  }

  scene->addConnection(m_tmpConnection, m_startPort);

  m_isUsing = true;
  m_isNodeSelectable = false;
}

void ConnectionCreateTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  if (!m_startPort) {
    return;
  }

  if (canConnectToPort(scene, event)) {
    m_tmpConnection->changePenStyle(TmpConnection::Connectable);
    m_tmpConnection->redraw(m_startPort, event->scenePos());
    return;
  }

  if (canConnectToConnector(scene, event)) {
    m_tmpConnection->changePenStyle(TmpConnection::Connectable);
    m_tmpConnection->redraw(m_startPort, event->scenePos());
    return;
  }
  m_tmpConnection->changePenStyle(TmpConnection::Connecting);
  m_tmpConnection->redraw(m_startPort, event->scenePos());
}

void ConnectionCreateTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (!m_startPort) {
    return;
  }

  m_isUsing = false;
  m_isNodeSelectable = true;

  scene->removeConnection(m_tmpConnection);
  if (canConnectToPort(scene, event)) {
    Port* endPort = scene->findPort(event->scenePos());
    decideConnectToPort(scene, endPort);
    return;
  }

  if (canConnectToConnector(scene, event)) {
    Connection* dstConnection = scene->findConnection(event->scenePos());
    decideConnectToConnector(scene, event->scenePos(), dstConnection);
    return;
  }
}

void ConnectionCreateTool::mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void ConnectionCreateTool::keyPressEvent(Scene* scene, QKeyEvent* event) {
  if (Qt::Key_Delete == event->key()) {
    Editor::getInstance()->addCommand(new NodeRemoveCommand(scene, scene->selectedNodes()));
  }
}

void ConnectionCreateTool::keyReleaseEvent(Scene* scene, QKeyEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void ConnectionCreateTool::decideConnectToPort(Scene* scene, Port* endPort) {
  Connection* connection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
  ConnectToPortCommand* command = new ConnectToPortCommand(scene, connection, m_startPort, endPort);
  Editor::getInstance()->addCommand(command);

  m_startPort = nullptr;
}

void ConnectionCreateTool::decideConnectToConnector(Scene* scene, QPointF mouseReleaseScenePos,
                                                    Connection* dstConnection) {
  Connection* connection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
  Connector* connector = ConnectorFactory::getInstance()->createConnector(CONNECTOR, connection);
  connector->setPos(dstConnection->closeCenter(mouseReleaseScenePos) + connector->centerOffset());
  ConnectToConnectorCommand* command =
      new ConnectToConnectorCommand(scene, connection, m_startPort, connector, dstConnection);
  Editor::getInstance()->addCommand(command);

  m_startPort = nullptr;
}

void ConnectionCreateTool::addTmpConnector(Scene* scene, Port* startPort) {
}

void ConnectionCreateTool::redrawTmpConnector(QPointF nowScenePos) {
}

void ConnectionCreateTool::decideConnector(Scene* scene, Port* endPort) {
}

void ConnectionCreateTool::removeTmpConnector(Scene* scene) {
}

bool ConnectionCreateTool::canConnect(Scene* scene, QGraphicsSceneMouseEvent* event) const {
  // when event position exist port and connection, prioritize port connection.
  if (canConnectToPort(scene, event)) {
    return true;
  }
  if (canConnectToConnector(scene, event)) {
    return true;
  }
  return false;
}

bool ConnectionCreateTool::canConnectToPort(Scene* scene, QGraphicsSceneMouseEvent* event) const {
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

bool ConnectionCreateTool::canConnectToConnector(Scene* scene, QGraphicsSceneMouseEvent* event) const {
  QList<Connection*> connections = scene->findConnections(event->scenePos());
  // now connection creating, so m_tmpConnection always contains in connections.
  // but this function need to find connect to connection, so remove m_tmpConnection.
  connections.removeOne(m_tmpConnection);

  if (0 == connections.count()) {
    return false;
  }
  return true;
}
