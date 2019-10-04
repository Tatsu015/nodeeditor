#include "PortRemoveCommand.h"
#include "AbstractNode.h"
#include "Connection.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"

PortRemoveCommand::PortRemoveCommand(Scene* scene, Sheet* sheet, AbstractNode* node, Port* port)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_node(node), m_port(port) {
  foreach (Connection* connection, m_port->connections()) {
    ConnectionInfo* connectionInfo = new ConnectionInfo();
    connectionInfo->m_connection = connection;
    connectionInfo->m_oppositeSidePort = connection->oppositeSidePort(m_port);
    m_connectionInfos << connectionInfo;
  }
}

PortRemoveCommand::~PortRemoveCommand() {
}

void PortRemoveCommand::redo() {
  foreach (ConnectionInfo* connectionInfo, m_connectionInfos) {
    Connection* connection = connectionInfo->m_connection;
    Port* oppositeSidePort = connectionInfo->m_oppositeSidePort;

    oppositeSidePort->removeConnection(connection);
    m_port->removeConnection(connection);
    Connection::Edge edge = connection->whichEdge(oppositeSidePort);
    if (Connection::Start == edge) {
      connection->removeStartPort();
    } else {
      connection->removeEndPort();
    }
    m_sheet->removeConnection(connection);
    m_scene->removeConnection(connection);
  }
  m_node->removePort(m_port);
  m_scene->removeItem(m_port);
  m_port->setParentItem(nullptr);
  m_node->redraw();
}

void PortRemoveCommand::undo() {
  m_node->addInputPort(m_port);
  m_port->setParentItem(m_node);

  foreach (ConnectionInfo* connectionInfo, m_connectionInfos) {
    Connection* connection = connectionInfo->m_connection;
    Port* oppositeSidePort = connectionInfo->m_oppositeSidePort;

    oppositeSidePort->addConnection(connection);
    m_port->addConnection(connection);
    Connection::Edge edge = connection->whichEdge(oppositeSidePort);
    if (Connection::Start == edge) {
      connection->setStartPort(oppositeSidePort);
      connection->setEndPort(m_port);
    } else {
      connection->setStartPort(m_port);
      connection->setEndPort(oppositeSidePort);
    }
    m_sheet->addConnection(connection);
    m_scene->addConnection(connection);
  }

  m_node->redraw();
}
