#include "NodeAddCommand.h"
#include "AbstractNode.h"
#include "Scene.h"
#include "Sheet.h"

NodeAddCommand::NodeAddCommand(Scene* scene, Sheet* sheet, AbstractNode* node, QPointF addScenePos)
    : QUndoCommand(), m_scene(scene), m_sheet(sheet), m_node(node), m_addScenePos(addScenePos) {
}

NodeAddCommand::~NodeAddCommand() {
}

void NodeAddCommand::redo() {
  m_scene->changeSheet(m_sheet);
  m_node->setPos(m_addScenePos);
  m_scene->addNode(m_node);
  m_sheet->addNode(m_node);
}

void NodeAddCommand::undo() {
  m_scene->changeSheet(m_sheet);
  m_scene->removeNode(m_node);
  m_sheet->removeNode(m_node);
}
