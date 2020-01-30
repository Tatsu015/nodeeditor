#include "ConnectToPortCommand.h"
#include "AbstractConnection.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"

ConnectToPortCommand::ConnectToPortCommand(Scene* scene, Sheet* sheet, AbstractConnection* connection, Port* startPort,
                                           Port* endPort, QList<QPointF> vertexes)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_connection(connection), m_startPort(startPort),
      m_endPort(endPort), m_vertexes(vertexes) {
}

ConnectToPortCommand::~ConnectToPortCommand() {
}

void ConnectToPortCommand::redo() {
  m_scene->changeSheet(m_sheet);

  m_connection->setStartPort(m_startPort);
  m_connection->setStartPos(m_startPort->endOfPortPos());
  m_startPort->addConnection(m_connection);

  m_connection->setEndPort(m_endPort);
  m_connection->setEndPos(m_endPort->endOfPortPos());
  m_endPort->addConnection(m_connection);

  foreach (QPointF vertex, m_vertexes) { m_connection->addVertex(vertex); }

  m_sheet->addConnection(m_connection);
  m_scene->addConnection(m_connection);
  m_connection->redraw();
  m_connection->created();
}

void ConnectToPortCommand::undo() {
  m_scene->changeSheet(m_sheet);

  m_scene->removeConnection(m_connection);
  m_sheet->removeConnection(m_connection);

  m_endPort->removeConnection(m_connection);
  m_connection->removeEndPort();

  m_startPort->removeConnection(m_connection);
  m_connection->removeStartPort();
}
