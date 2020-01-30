#include "VertexRemoveCommand.h"
#include "AbstractConnection.h"
#include "Scene.h"
#include "Sheet.h"
#include "VertexHandle.h"
#include <QList>

VertexRemoveCommand::VertexRemoveCommand(Scene* scene, Sheet* sheet, VertexHandle* removedVertexHandle)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_removedVertexHandle(removedVertexHandle) {
}

VertexRemoveCommand::~VertexRemoveCommand() {
}

void VertexRemoveCommand::redo() {
  // TODO this code do not work
  //  m_scene->changeSheet(m_sheet);
  m_targetConnection = m_removedVertexHandle->connection();
  m_index = m_targetConnection->vertexes().indexOf(m_removedVertexHandle->pos());
  m_targetConnection->removeVertex(m_removedVertexHandle);
  m_scene->removeItem(m_removedVertexHandle);
}

void VertexRemoveCommand::undo() {
  // TODO this code do not work
  //  m_scene->changeSheet(m_sheet);
  m_targetConnection->insertVertex(m_removedVertexHandle, m_index);
  m_targetConnection->redraw();
}
