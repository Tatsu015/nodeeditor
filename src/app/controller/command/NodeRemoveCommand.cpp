#include "NodeRemoveCommand.h"
#include "AbstractNode.h"
#include "Scene.h"

NodeRemoveCommand::NodeRemoveCommand(Scene* scene, QList<AbstractNode*> nodes)
 : QUndoCommand(), m_scene(scene) {
  foreach (AbstractNode* node, nodes) {
    NodeRemoveInfo* nodeRemoveInfo = new NodeRemoveInfo();
    nodeRemoveInfo->m_node = node;
    m_nodeRemoveInfos << nodeRemoveInfo;
  }
}

NodeRemoveCommand::~NodeRemoveCommand()
{
}

void NodeRemoveCommand::redo()
{
  foreach (NodeRemoveInfo* nodeRemoveInfo, m_nodeRemoveInfos) {
    m_scene->removeNode(nodeRemoveInfo->m_node);
  }
}

void NodeRemoveCommand::undo()
{
  foreach (NodeRemoveInfo* nodeRemoveInfo, m_nodeRemoveInfos) {
    m_scene->addNode(nodeRemoveInfo->m_node, nodeRemoveInfo->m_node->scenePos());
    nodeRemoveInfo->m_node->redraw();
  }
}
