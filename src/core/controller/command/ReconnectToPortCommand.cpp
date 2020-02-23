#include "ReconnectToPortCommand.h"
#include "AbstractConnection.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"

ReconnectToPortCommand::ReconnectToPortCommand(Scene* scene, Sheet* sheet, AbstractConnection* connection,
                                               Port* lastPort, Port* targetPort, bool isMoveStartPort)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_connection(connection), m_lastPort(lastPort),
      m_targetPort(targetPort) {
}

ReconnectToPortCommand::~ReconnectToPortCommand() {
}

void ReconnectToPortCommand::redo() {
  m_scene->changeSheet(m_sheet);

  if (m_isMoveStartPort) {
    m_connection->removeStartPort();
    m_lastPort->removeConnection(m_connection);

    m_connection->setStartPort(m_targetPort);
    m_connection->setStartPos(m_targetPort->endOfPortPos());
  } else {
    m_connection->removeEndPort();
    m_lastPort->removeConnection(m_connection);

    m_connection->setEndPort(m_targetPort);
    m_connection->setEndPos(m_targetPort->endOfPortPos());
  }
  m_targetPort->addConnection(m_connection);
}

void ReconnectToPortCommand::undo() {
  m_scene->changeSheet(m_sheet);
  if (m_isMoveStartPort) {
    m_connection->removeStartPort();
    m_targetPort->removeConnection(m_connection);
    m_connection->setStartPort(m_lastPort);
    m_connection->setStartPos(m_lastPort->endOfPortPos());
  } else {
    m_connection->removeEndPort();
    m_targetPort->removeConnection(m_connection);
    m_connection->setEndPort(m_lastPort);
    m_connection->setEndPos(m_lastPort->endOfPortPos());
  }
  m_lastPort->addConnection(m_connection);
}
