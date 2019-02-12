#include "NodeEditTool.h"
#include <QAction>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "AbstractNode.h"
#include "Define.h"
#include "Editor.h"
#include "GuideLine.h"
#include "NodeAddCommand.h"
#include "NodeFactory.h"
#include "NodeMoveCommand.h"
#include "NodeRemoveCommand.h"
#include "Scene.h"

const static qreal GUIDELINE_DRAWOVER_SIZE = 10;

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
  if (isSelectedNodesPressed(event->scenePos(), scene)) {
    m_isNodeSelected = true;
    m_isNodeSelectable = false;
  }
}

void NodeEditTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(event);
  drawGuideLine(scene);
}

void NodeEditTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  scene->clearGuideLine();

  if (m_isNodeSelected) {
    QPointF startScenePos = event->buttonDownScenePos(Qt::LeftButton);
    QPointF endScenePos = event->scenePos();
    QPointF diffScenePos = endScenePos - startScenePos;
    if (diffScenePos.manhattanLength() < 0.01) {
      return;
    }
    Editor::getInstance()->addCommand(new NodeMoveCommand(scene, scene->selectedNodes(), diffScenePos));
  }
  m_isNodeSelected = false;
  m_isNodeSelectable = true;
}

void NodeEditTool::mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  AbstractNode* node = NodeFactory::getInstance()->createNode(m_activeNodeType);
  QPointF ofs(node->boundingRect().center());
  QPointF addScenePos = event->scenePos() - ofs;
  Editor::getInstance()->addCommand(new NodeAddCommand(scene, node, addScenePos));
}

void NodeEditTool::keyPressEvent(Scene* scene, QKeyEvent* event) {
  if (Qt::Key_Delete == event->key()) {
    Editor::getInstance()->addCommand(new NodeRemoveCommand(scene, scene->selectedNodes()));
  }
}

void NodeEditTool::keyReleaseEvent(Scene* scene, QKeyEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

QStringList NodeEditTool::nodeTypes() const { return m_nodeTypes; }

bool NodeEditTool::isSelectedNodesPressed(QPointF scenePos, Scene* scene) {
  foreach (AbstractNode* node, scene->findNodes(scenePos)) {
    if (node->isSelected()) {
      return true;
    }
  }
  return false;
}

void NodeEditTool::setActiveNodeType(const QString& activeNodeType) { m_activeNodeType = activeNodeType; }

void NodeEditTool::drawGuideLine(Scene* scene) {
  scene->clearGuideLine();

  QList<AbstractNode*> selectedNodes = scene->selectedNodes();
  if (0 == selectedNodes.count()) {
    return;
  }
  AbstractNode* movingNode = dynamic_cast<AbstractNode*>(selectedNodes.first());
  if (!movingNode) {
    return;
  }

  drawTopGuideLineFromNearNodes(scene, movingNode);
  drawBottomGuideLineFromNearNodes(scene, movingNode);
  drawRightGuideLineFromNearNodes(scene, movingNode);
  drawLeftGuideLineFromNearNodes(scene, movingNode);
}

void NodeEditTool::drawTopGuideLineFromNearNodes(Scene* scene, AbstractNode* movingNode) {
  QList<AbstractNode*> nearNodes;
  nearNodes.append(scene->nearTopNodes(movingNode->top(), Scene::OnlyUnselected));
  nearNodes.append(scene->nearTopNodes(movingNode->bottom(), Scene::OnlyUnselected));

  foreach (AbstractNode* nearNode, nearNodes) {
    qreal y = nearNode->top();
    qreal left = qMin(nearNode->left(), movingNode->left()) - GUIDELINE_DRAWOVER_SIZE;
    qreal right = qMax(nearNode->right(), movingNode->right()) + GUIDELINE_DRAWOVER_SIZE;
    GuideLine* guideLine = new GuideLine(left, y, right, y);
    scene->addGuideLine(guideLine);
  }
}

void NodeEditTool::drawBottomGuideLineFromNearNodes(Scene* scene, AbstractNode* movingNode) {
  QList<AbstractNode*> nearNodes;
  nearNodes.append(scene->nearBottomNodes(movingNode->bottom(), Scene::OnlyUnselected));
  nearNodes.append(scene->nearBottomNodes(movingNode->top(), Scene::OnlyUnselected));

  foreach (AbstractNode* nearNode, nearNodes) {
    qreal y = nearNode->bottom();
    qreal left = qMin(nearNode->left(), movingNode->left()) - GUIDELINE_DRAWOVER_SIZE;
    qreal right = qMax(nearNode->right(), movingNode->right()) + GUIDELINE_DRAWOVER_SIZE;
    GuideLine* guideLine = new GuideLine(left, y, right, y);
    scene->addGuideLine(guideLine);
  }
}

void NodeEditTool::drawRightGuideLineFromNearNodes(Scene* scene, AbstractNode* movingNode) {
  QList<AbstractNode*> nearNodes;
  nearNodes.append(scene->nearRightNodes(movingNode->right(), Scene::OnlyUnselected));
  nearNodes.append(scene->nearRightNodes(movingNode->left(), Scene::OnlyUnselected));

  foreach (AbstractNode* nearNode, nearNodes) {
    qreal x = nearNode->right();
    qreal top = qMin(nearNode->top(), movingNode->top()) - GUIDELINE_DRAWOVER_SIZE;
    qreal bottom = qMax(nearNode->bottom(), movingNode->bottom()) + GUIDELINE_DRAWOVER_SIZE;
    GuideLine* guideLine = new GuideLine(x, top, x, bottom);
    scene->addGuideLine(guideLine);
  }
}

void NodeEditTool::drawLeftGuideLineFromNearNodes(Scene* scene, AbstractNode* movingNode) {
  QList<AbstractNode*> nearNodes;
  nearNodes.append(scene->nearLeftNodes(movingNode->left(), Scene::OnlyUnselected));
  nearNodes.append(scene->nearLeftNodes(movingNode->right(), Scene::OnlyUnselected));

  foreach (AbstractNode* nearNode, nearNodes) {
    qreal x = nearNode->left();
    qreal top = qMin(nearNode->top(), movingNode->top()) - GUIDELINE_DRAWOVER_SIZE;
    qreal bottom = qMax(nearNode->bottom(), movingNode->bottom()) + GUIDELINE_DRAWOVER_SIZE;
    GuideLine* guideLine = new GuideLine(x, top, x, bottom);
    scene->addGuideLine(guideLine);
  }
}
