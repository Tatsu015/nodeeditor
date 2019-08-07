#include "NodeRemoveCommand.h"
#include "AbstractNode.h"
#include "Connection.h"
#include "Connector.h"
#include "Port.h"
#include "Scene.h"

NodeRemoveCommand::NodeRemoveCommand(Scene* scene, QList<AbstractNode*> nodes) : QUndoCommand(), m_scene(scene) {
  QList<Connection*> checkedConnections;

  foreach (AbstractNode* node, nodes) {
    NodeRemoveInfo* nodeRemoveInfo = new NodeRemoveInfo();
    nodeRemoveInfo->m_node = node;
    foreach (Port* port, node->ports()) {
      foreach (Connection* connection, port->connections()) {
        if (checkedConnections.contains(connection)) {
          continue;
        }
        checkedConnections << connection;

        ConnectionInfo* connectionInfo = new ConnectionInfo();
        connectionInfo->m_connection = connection;

        if (connection->startPort()) {
          connectionInfo->m_startPortNumber = connection->startPort()->number();
          connectionInfo->m_startNodeName = connection->startPort()->parentNode()->name();
        }
        if (connection->endPort()) {
          connectionInfo->m_endPortNumber = connection->endPort()->number();
          connectionInfo->m_endNodeName = connection->endPort()->parentNode()->name();
        }
        if (connection->endConnector()) {
          connectionInfo->m_endConnectorInfo.m_connector = connection->endConnector();
          connectionInfo->m_endConnectorInfo.m_dstConnection = connection->endConnector()->dstConnection();
        }

        nodeRemoveInfo->m_connectionInfos << connectionInfo;
      }
    }
    m_nodeRemoveInfos << nodeRemoveInfo;
  }
}

NodeRemoveCommand::~NodeRemoveCommand() {
}

void NodeRemoveCommand::redo() {
  foreach (NodeRemoveInfo* nodeRemoveInfo, m_nodeRemoveInfos) { m_scene->removeNode(nodeRemoveInfo->m_node); }
}

void NodeRemoveCommand::undo() {
  // when connect distination node do not exist, connection cannot create
  // so first loop create all nodes
  foreach (NodeRemoveInfo* nodeRemoveInfo, m_nodeRemoveInfos) {
    m_scene->addNode(nodeRemoveInfo->m_node, nodeRemoveInfo->m_node->scenePos());
  }

  foreach (NodeRemoveInfo* nodeRemoveInfo, m_nodeRemoveInfos) {
    foreach (ConnectionInfo* connectionInfo, nodeRemoveInfo->m_connectionInfos) {
      if (connectionInfo->m_endConnectorInfo.m_connector) {
        connectionInfo->m_endConnectorInfo.m_dstConnection->addBranchConnector(
            connectionInfo->m_endConnectorInfo.m_connector);
      }
    }
  }
  // second loop create connections
  foreach (NodeRemoveInfo* nodeRemoveInfo, m_nodeRemoveInfos) {
    foreach (ConnectionInfo* connectionInfo, nodeRemoveInfo->m_connectionInfos) {
      if (connectionInfo->m_endConnectorInfo.m_connector) {
        m_scene->addConnection(connectionInfo->m_connection, connectionInfo->m_startNodeName,
                               connectionInfo->m_startPortNumber, connectionInfo->m_endConnectorInfo.m_connector,
                               connectionInfo->m_endConnectorInfo.m_dstConnection);
      } else {
        m_scene->addConnection(connectionInfo->m_connection, connectionInfo->m_startNodeName,
                               connectionInfo->m_startPortNumber, connectionInfo->m_endNodeName,
                               connectionInfo->m_endPortNumber);
      }
    }
    nodeRemoveInfo->m_node->redraw();
  }
}
