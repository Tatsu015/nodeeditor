#include "NodeAddCommand.h"
#include "Scene.h"

NodeAddCommand::NodeAddCommand(Scene* scene, AbstractNode* node, QPointF addScenePos)
    : QUndoCommand(), m_scene(scene), m_node(node), m_addScenePos(addScenePos) {}

NodeAddCommand::~NodeAddCommand() {}

void NodeAddCommand::redo() { m_scene->addNode(m_node, m_addScenePos); }

void NodeAddCommand::undo() { m_scene->removeNode(m_node); }
