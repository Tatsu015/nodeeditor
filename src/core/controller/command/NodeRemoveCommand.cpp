#include "NodeRemoveCommand.h"
#include "AbstractNode.h"
#include "Connection.h"
#include "Connector.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"

NodeRemoveCommand::ConnectionInfo::ConnectionInfo(Connection* connection, Port* startPort, Port* endPort)
    : m_connection(connection), m_startPort(startPort), m_endPort(endPort) {
}

NodeRemoveCommand::ConnectionInfo::~ConnectionInfo() {
}

void NodeRemoveCommand::ConnectionInfo::reconnect() {
  if (m_endPort) {
    m_endPort->addConnection(m_connection);
    m_connection->setEndPort(m_endPort);
  } else if (m_startPort) {
    m_startPort->addConnection(m_connection);
    m_connection->setStartPort(m_startPort);
  }
}

NodeRemoveCommand::NodeRemoveCommand(Scene* scene, Sheet* sheet, QList<AbstractNode*> nodes)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet) {
  m_nodes = nodes;
}

NodeRemoveCommand::~NodeRemoveCommand() {
}

void NodeRemoveCommand::redo() {
  foreach (AbstractNode* node, m_nodes) {
    m_sheet->removeNode(node);
    m_scene->removeNode(node);
  }
  foreach (AbstractNode* node, m_nodes) {
    foreach (Port* port, node->ports()) {
      foreach (Connection* connection, port->connections()) {
        if (m_connections.contains(connection)) {
          continue;
        }
        // connection which start or end node is not removed, need to disconnect from remain node.
        // both side node removed, unneed to disconnect because when undo/redo reconnect.
        if (isStartNodeRemoved(connection) && !isEndNodeRemoved(connection)) {
          Port* port = connection->endPort();
          port->removeConnection(connection);
          connection->removeEndPort();
          ConnectionInfo* connectionInfo = new ConnectionInfo(connection, nullptr, port);
          m_connectionInfos << connectionInfo;
        } else if (!isStartNodeRemoved(connection) && isEndNodeRemoved(connection)) {
          Port* port = connection->startPort();
          port->removeConnection(connection);
          connection->removeStartPort();
          ConnectionInfo* connectionInfo = new ConnectionInfo(connection, port, nullptr);
          m_connectionInfos << connectionInfo;
        }
        m_connections << connection;
        m_sheet->removeConnection(connection);
        m_scene->removeConnection(connection);
      }
    }
  }
}

void NodeRemoveCommand::undo() {
  foreach (AbstractNode* node, m_nodes) {
    m_sheet->addNode(node);
    m_scene->addNode(node);
  }
  foreach (Connection* connection, m_connections) {
    m_sheet->addConnection(connection);
    m_scene->addConnection(connection);
  }
  foreach (ConnectionInfo* connectionInfo, m_connectionInfos) { connectionInfo->reconnect(); }
}

bool NodeRemoveCommand::isStartNodeRemoved(const Connection* connection) const {
  AbstractNode* startNode = connection->startPort()->parentNode();
  return m_nodes.contains(startNode);
}

bool NodeRemoveCommand::isEndNodeRemoved(const Connection* connection) const {
  AbstractNode* endNode = connection->endPort()->parentNode();
  return m_nodes.contains(endNode);
}
