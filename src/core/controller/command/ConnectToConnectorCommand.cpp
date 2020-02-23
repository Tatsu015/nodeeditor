#include "ConnectToConnectorCommand.h"
#include "AbstractConnection.h"
#include "Connector.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"

ConnectToConnectorCommand::ConnectToConnectorCommand(Scene* scene, Sheet* sheet, AbstractConnection* connection,
                                                     Port* startPort, Connector* endConnector,
                                                     AbstractConnection* dstConnection, QList<QPointF> vertexes)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_connection(connection), m_startPort(startPort),
      m_endConnector(endConnector), m_dstConnection(dstConnection), m_vertexes(vertexes) {
}

ConnectToConnectorCommand::~ConnectToConnectorCommand() {
}

void ConnectToConnectorCommand::redo() {
  m_scene->changeSheet(m_sheet);

  m_connection->setStartPort(m_startPort);
  //  m_connection->setStartPos(m_startPort->endOfPortPos());
  m_startPort->addConnection(m_connection);

  m_connection->setEndConnector(m_endConnector);
  //  m_connection->setEndPos(m_endConnector->centerScenePos());
  foreach (QPointF vertex, m_vertexes) { m_connection->addVertex(vertex); }

  m_endConnector->setDstConnection(m_dstConnection);
  m_endConnector->setSrcConnection(m_connection);
  m_dstConnection->addBranchConnector(m_endConnector);

  m_sheet->addConnection(m_connection);
  m_scene->addItem(m_connection);
  m_connection->redraw();
  m_connection->created();
}

void ConnectToConnectorCommand::undo() {
  m_scene->changeSheet(m_sheet);

  m_sheet->removeConnection(m_connection);
  m_scene->removeConnection(m_connection);
  // TODO why need???
  m_scene->removeItem(m_endConnector);

  m_dstConnection->removeBranchConnector(m_endConnector);
  m_endConnector->removeSrcConnection();
  m_endConnector->removeDstConnection();
  m_connection->removeEndConnector();

  m_startPort->removeConnection(m_connection);
  m_connection->removeStartPort();
}
