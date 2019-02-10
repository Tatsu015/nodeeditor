#include "NodeRemoveCommand.h"
#include "AbstractNode.h"
#include "Scene.h"

NodeRemoveCommand::NodeRemoveCommand(Scene* scene, AbstractNode* node, QPointF addScenePos)
 : QUndoCommand(), m_scene(scene), m_node(node), m_addScenePos(addScenePos) {}

NodeRemoveCommand::~NodeRemoveCommand()
{
}

void NodeRemoveCommand::redo()
{
  m_scene->removeNode(m_node);
}

void NodeRemoveCommand::undo()
{
  m_scene->addNode(m_node, m_addScenePos);
}
