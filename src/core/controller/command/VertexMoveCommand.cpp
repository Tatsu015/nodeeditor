#include "VertexMoveCommand.h"
#include "AbstractConnection.h"
#include "Scene.h"
#include "Sheet.h"
#include "VertexHandle.h"

VertexMoveCommand::VertexMoveCommand(Scene* scene, Sheet* sheet, VertexHandle* movedVertexHandle, QPointF diff)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_movedVertexHandle(movedVertexHandle), m_diff(diff) {
  m_startScenePos = m_movedVertexHandle->pos() - diff;
  m_endScenePos = m_movedVertexHandle->pos();
}

VertexMoveCommand::~VertexMoveCommand() {
}

void VertexMoveCommand::redo() {
  // TODO this code do not work
  //  m_scene->changeSheet(m_sheet);
  m_movedVertexHandle->setPos(m_endScenePos);
  m_movedVertexHandle->connection()->redraw();
  // keep connection selected when finish vertex move
  m_movedVertexHandle->connection()->setSelected(true);
}

void VertexMoveCommand::undo() {
  // TODO this code do not work
  //  m_scene->changeSheet(m_sheet);
  m_movedVertexHandle->setPos(m_startScenePos);
  m_movedVertexHandle->connection()->redraw();
}
