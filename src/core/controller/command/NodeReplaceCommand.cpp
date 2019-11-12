#include "NodeReplaceCommand.h"
#include "AbstractNode.h"
#include "Connection.h"
#include "Port.h"
#include "Scene.h"
#include "Sheet.h"

NodeReplaceCommand::NodeReplaceCommand(Scene* scene, Sheet* sheet, AbstractNode* srcNode, AbstractNode* dstNode)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_srcNode(srcNode), m_dstNode(dstNode) {
}

NodeReplaceCommand::~NodeReplaceCommand() {
}

void NodeReplaceCommand::redo() {
  m_dstNode->setPos(m_srcNode->pos());
  foreach (Port* oldPort, m_srcNode->ports()) {
    Port* newPort = m_dstNode->port(oldPort->number());
    foreach (Connection* connection, oldPort->connections()) {
      oldPort->removeConnection(connection);
      newPort->addConnection(connection);
      if (Connection::End == connection->whichEdge(oldPort)) {
        connection->removeEndPort();
        connection->setEndPort(newPort);
      } else {
        connection->removeStartPort();
        connection->setStartPort(newPort);
      }
    }
  }

  m_sheet->addNode(m_dstNode);
  m_sheet->removeNode(m_srcNode);
  m_scene->addNode(m_dstNode);
  m_scene->removeNode(m_srcNode);
}

void NodeReplaceCommand::undo() {
  m_srcNode->setPos(m_dstNode->pos());
  foreach (Port* newPort, m_dstNode->ports()) {
    Port* oldPort = m_srcNode->port(newPort->number());
    foreach (Connection* connection, newPort->connections()) {
      newPort->removeConnection(connection);
      oldPort->addConnection(connection);
      if (Connection::End == connection->whichEdge(newPort)) {
        connection->removeEndPort();
        connection->setEndPort(oldPort);
      } else {
        connection->removeStartPort();
        connection->setStartPort(oldPort);
      }
    }
  }

  m_sheet->addNode(m_srcNode);
  m_sheet->removeNode(m_dstNode);
  m_scene->addNode(m_srcNode);
  m_scene->removeNode(m_dstNode);
}
