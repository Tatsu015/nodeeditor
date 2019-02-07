#include "NodeEditTool.h"
#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include "AbstractNode.h"
#include "Define.h"
#include "NodeFactory.h"
#include "Scene.h"

NodeEditTool::NodeEditTool() : AbstractTool(TOOL_NODE_CREATE) {
  m_nodeTypes.append(NODE_IN);
  m_nodeTypes.append(NODE_OUT);
  m_nodeTypes.append(NODE_AND);
  m_nodeTypes.append(NODE_OR);

  m_activeNodeType = m_nodeTypes.first();
}

NodeEditTool::~NodeEditTool() {}

void NodeEditTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void NodeEditTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void NodeEditTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void NodeEditTool::mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  AbstractNode* node = NodeFactory::getInstance()->createNode(m_activeNodeType);
  QPointF ofs(node->boundingRect().center());
  scene->addNode(node, QPointF(event->scenePos() - ofs));
}

QStringList NodeEditTool::nodeTypes() const { return m_nodeTypes; }

void NodeEditTool::setActiveNodeType(const QString& activeNodeType) { m_activeNodeType = activeNodeType; }
