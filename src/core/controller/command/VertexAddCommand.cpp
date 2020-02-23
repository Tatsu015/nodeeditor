#include "VertexAddCommand.h"
#include "AbstractConnection.h"
#include "Scene.h"
#include "Sheet.h"
#include "VertexHandle.h"
#include <QList>

VertexAddCommand::VertexAddCommand(Scene* scene, Sheet* sheet, VertexHandle* addVertexHandle,
                                   AbstractConnection* targetConnection, int32_t areaIndex)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_addVertexHandle(addVertexHandle),
      m_targetConnection(targetConnection), m_areaIndex(areaIndex) {
}

VertexAddCommand::~VertexAddCommand() {
}

void VertexAddCommand::redo() {
  // TODO this code do not work
  //  m_scene->changeSheet(m_sheet);
  m_targetConnection->insertVertex(m_addVertexHandle, m_areaIndex);
  m_targetConnection->redraw();
}

void VertexAddCommand::undo() {
  // TODO this code do not work
  //  m_scene->changeSheet(m_sheet);
  m_targetConnection->removeVertex(m_addVertexHandle);
  m_targetConnection->redraw();
  m_scene->removeItem(m_addVertexHandle);
}
