#include "ConnectToConnectorCommand.h"
#include "Scene.h"

ConnectToConnectorCommand::ConnectToConnectorCommand(Scene* scene, Connection* connection, Port* startPort,
                                                     Connector* endConnector, Connection* dstConnection)
    : QUndoCommand(), m_scene(scene), m_connection(connection), m_startPort(startPort), m_endConnector(endConnector),
      m_dstConnection(dstConnection) {
}

ConnectToConnectorCommand::~ConnectToConnectorCommand() {
}

void ConnectToConnectorCommand::redo() {
  m_scene->addConnection(m_connection, m_startPort, m_endConnector, m_dstConnection);
}

void ConnectToConnectorCommand::undo() {
  m_scene->removeConnection(m_connection);
}
