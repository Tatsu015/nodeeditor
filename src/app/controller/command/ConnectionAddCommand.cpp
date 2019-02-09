#include "ConnectionAddCommand.h"
#include "Scene.h"

ConnectionAddCommand::ConnectionAddCommand(Scene* scene, Connection* connection, Port* startPort, Port* endPort)
    : QUndoCommand(), m_scene(scene), m_connection(connection), m_startPort(startPort), m_endPort(endPort) {}

ConnectionAddCommand::~ConnectionAddCommand() {}

void ConnectionAddCommand::redo() { m_scene->addConnection(m_connection, m_startPort, m_endPort); }

void ConnectionAddCommand::undo() { m_scene->removeConnection(m_connection); }
