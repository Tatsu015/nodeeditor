#include "NodeRemoveCommand.h"
#include "AbstractConnection.h"
#include "AbstractNode.h"
#include "Connector.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"

NodeRemoveCommand::ConnectionInfo::ConnectionInfo(AbstractConnection* connection, Port* startPort, Port* endPort)
    : m_connection(connection), m_startPort(startPort), m_endPort(endPort) {
}

NodeRemoveCommand::ConnectionInfo::~ConnectionInfo() {
}

void NodeRemoveCommand::ConnectionInfo::reconnect() {
  if (m_endPort) {
    m_endPort->addConnection(m_connection);
    m_connection->setEndPort(m_endPort);
  }
  if (m_startPort) {
    m_startPort->addConnection(m_connection);
    m_connection->setStartPort(m_startPort);
  }
}

NodeRemoveCommand::NodeRemoveCommand(Scene* scene, Sheet* sheet, QList<AbstractNode*> nodes,
                                     QList<AbstractConnection*> connections)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_nodes(nodes), m_connections(connections) {
}

NodeRemoveCommand::~NodeRemoveCommand() {
}

void NodeRemoveCommand::redo() {
  foreach (AbstractNode* node, m_nodes) {
    m_sheet->removeNode(node);
    m_scene->removeNode(node);
    foreach (Port* port, node->ports()) {
      foreach (AbstractConnection* connection, port->connections()) {
        if (!m_connections.contains(connection)) {
          m_connections << connection;
        }
      }
    }
  }
  foreach (AbstractConnection* connection, m_connections) {
    m_sheet->removeConnection(connection);
    m_scene->removeConnection(connection);

    // both side node removed, unneed to disconnect.
    Port* startPort = connection->startPort();
    Port* endPort = connection->endPort();
    if (isStartNodeRemoved(connection) && isEndNodeRemoved(connection)) {
      continue;
    }

    // connection which start, end or both node removed, need to disconnect from remain node.
    if (isStartNodeRemoved(connection) && !isEndNodeRemoved(connection)) {
      endPort->removeConnection(connection);
      connection->removeEndPort();
    } else if (!isStartNodeRemoved(connection) && isEndNodeRemoved(connection)) {
      startPort->removeConnection(connection);
      connection->removeStartPort();
    } else if (!isStartNodeRemoved(connection) && !isEndNodeRemoved(connection)) {
      endPort->removeConnection(connection);
      connection->removeEndPort();
      startPort->removeConnection(connection);
      connection->removeStartPort();
    }
    ConnectionInfo* connectionInfo = new ConnectionInfo(connection, startPort, endPort);
    m_connectionInfos << connectionInfo;
  }
}

void NodeRemoveCommand::undo() {
  foreach (AbstractNode* node, m_nodes) {
    m_sheet->addNode(node);
    m_scene->addNode(node);
    node->created();
  }
  foreach (AbstractConnection* connection, m_connections) {
    m_sheet->addConnection(connection);
    m_scene->addConnection(connection);
    connection->created();
  }
  foreach (ConnectionInfo* connectionInfo, m_connectionInfos) { connectionInfo->reconnect(); }
}

bool NodeRemoveCommand::isStartNodeRemoved(const AbstractConnection* connection) const {
  if (connection->hasStartPort()) {
    AbstractNode* startNode = connection->startPort()->parentNode();
    return m_nodes.contains(startNode);
  }
  return false;
}

bool NodeRemoveCommand::isEndNodeRemoved(const AbstractConnection* connection) const {
  if (connection->hasEndPort()) {
    AbstractNode* endNode = connection->endPort()->parentNode();
    return m_nodes.contains(endNode);
  }
  return false;
}
