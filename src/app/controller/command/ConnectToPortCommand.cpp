#include "ConnectToPortCommand.h"
#include "Scene.h"

ConnectToPortCommand::ConnectToPortCommand(Scene* scene, Connection* connection, Port* startPort, Port* endPort)
    : QUndoCommand(), m_scene(scene), m_connection(connection), m_startPort(startPort), m_endPort(endPort) {}

ConnectToPortCommand::~ConnectToPortCommand() {}

void ConnectToPortCommand::redo() {
    m_scene->addConnection(m_connection, m_startPort, m_endPort);
}

void ConnectToPortCommand::undo() { m_scene->removeConnection(m_connection); }
