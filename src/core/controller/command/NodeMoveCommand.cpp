#include "NodeMoveCommand.h"
#include "AbstractNode.h"
#include "Scene.h"

NodeMoveCommand::NodeMoveCommand(Scene* scene, QList<AbstractNode*> nodes, QPointF diff)
    : QUndoCommand(), m_scene(scene), m_diff(diff) {
  foreach (AbstractNode* node, nodes) {
    NodeMoveInfo* nodeMoveInfo = new NodeMoveInfo();
    nodeMoveInfo->m_node = node;
    nodeMoveInfo->m_startScenePos = node->pos() - diff;
    nodeMoveInfo->m_endScenePos = node->pos();
    m_nodeMovenfos << nodeMoveInfo;
  }
}

NodeMoveCommand::~NodeMoveCommand() {
}

void NodeMoveCommand::redo() {
  foreach (NodeMoveInfo* nodeMoveInfo, m_nodeMovenfos) {
    nodeMoveInfo->m_node->setPos(nodeMoveInfo->m_endScenePos);
    nodeMoveInfo->m_node->redraw();
  }
}

void NodeMoveCommand::undo() {
  foreach (NodeMoveInfo* nodeMoveInfo, m_nodeMovenfos) {
    nodeMoveInfo->m_node->setPos(nodeMoveInfo->m_startScenePos);
    nodeMoveInfo->m_node->redraw();
  }
}
