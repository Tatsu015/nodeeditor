#include "NodeEditTool.h"
#include "AbstractNode.h"
#include "Define.h"
#include "Editor.h"
#include "GuideLine.h"
#include "NodeAddCommand.h"
#include "NodeFactory.h"
#include "NodeFactory.h"
#include "NodeMoveCommand.h"
#include "NodeRemoveCommand.h"
#include "Project.h"
#include "Scene.h"
#include "Sheet.h"
#include <QAction>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>

const static qreal GUIDELINE_DRAWOVER_SIZE = 10;

NodeEditTool::NodeEditTool() : AbstractTool(TOOL_NODE_CREATE) {
  m_nodeTypes = NodeFactory::getInstance()->nodeTypes();
  m_activeNodeType = m_nodeTypes.first();
}

NodeEditTool::~NodeEditTool() {
}

void NodeEditTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (scene->findNode(event->scenePos())) {
    m_isNodeMoving = true;
    m_isNodeSelectable = false;
  }
}

void NodeEditTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(event);
  drawGuideLine(scene);
}

void NodeEditTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  scene->clearGuideLine();
  if (m_isNodeMoving) {
    QPointF startScenePos = event->buttonDownScenePos(Qt::LeftButton);
    QPointF endScenePos = event->scenePos();
    QPointF diffScenePos = endScenePos - startScenePos;
    if (diffScenePos.manhattanLength() > 0.01) {
      Editor::getInstance()->addCommand(
          new NodeMoveCommand(scene, scene->sheet(), scene->selectedNodes(), diffScenePos));
    }
  }
  m_isNodeMoving = false;
  m_isNodeSelectable = true;
}

void NodeEditTool::mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Sheet* activeSheet = scene->sheet();
  if (!activeSheet) {
    return;
  }
  AbstractNode* node = NodeFactory::getInstance()->createNode(activeSheet, m_activeNodeType);
  bool nodeNameVisible = Editor::getInstance()->project()->nodeNameVisible();
  node->setNameTextVisible(nodeNameVisible);
  QPointF addScenePos = event->scenePos() - node->centerOffset();
  Editor::getInstance()->addCommand(new NodeAddCommand(scene, activeSheet, node, addScenePos));
}

void NodeEditTool::keyPressEvent(Scene* scene, QKeyEvent* event) {
  if (Qt::Key_Delete == event->key()) {
    Sheet* activeSheet = scene->sheet();
    if (!activeSheet) {
      return;
    }
    Editor::getInstance()->addCommand(new NodeRemoveCommand(scene, activeSheet, scene->selectedNodes()));
  }
  if (Qt::Key_C == event->key() && Qt::ControlModifier == event->modifiers()) {
    captureSelectedNodes(scene);
  }
  if (Qt::Key_V == event->key() && Qt::ControlModifier == event->modifiers()) {
    pasteCopyNodes(scene);
  }
  if ((Qt::Key_Control == event->key()) && m_isNodeMoving) {
    QGuiApplication::setOverrideCursor(QCursor(Qt::DragCopyCursor));
    captureSelectedNodes(scene);
  }
}

void NodeEditTool::keyReleaseEvent(Scene* scene, QKeyEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
  QGuiApplication::restoreOverrideCursor();
}

QStringList NodeEditTool::nodeTypes() const {
  return m_nodeTypes;
}

bool NodeEditTool::isSelectedNodesPressed(QPointF scenePos, Scene* scene) {
  foreach (AbstractNode* node, scene->findNodes(scenePos)) {
    if (node->isSelected()) {
      return true;
    }
  }
  return false;
}

void NodeEditTool::setActiveNodeType(const QString& activeNodeType) {
  m_activeNodeType = activeNodeType;
}

void NodeEditTool::drawGuideLine(Scene* scene) {
  scene->clearGuideLine();

  if (!m_isNodeMoving) {
    return;
  }

  foreach (AbstractNode* movingNode, scene->selectedNodes()) {
    drawTopGuideLineFromNearNodes(scene, movingNode);
    drawBottomGuideLineFromNearNodes(scene, movingNode);
    drawRightGuideLineFromNearNodes(scene, movingNode);
    drawLeftGuideLineFromNearNodes(scene, movingNode);
  }
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

void NodeEditTool::captureSelectedNodes(Scene* scene) {
  m_copySrcNodes.clear();
  m_copySrcNodes << scene->selectedNodes();
  m_lastPastePos = QPointF();
}

void NodeEditTool::pasteCopyNodes(Scene* scene) {
  foreach (AbstractNode* node, scene->selectedNodes()) { node->setSelected(false); }
  foreach (AbstractNode* srcNode, m_copySrcNodes) {
    Sheet* sheet = scene->sheet();
    AbstractNode* copyNode = NodeFactory::getInstance()->createNode(sheet, srcNode->nodeType());
    copyNode->setPos(srcNode->pos() + m_lastPastePos + QPointF(10, 10));

    sheet->addNode(copyNode);
    scene->addNode(copyNode);
    copyNode->setSelected(true);
    srcNode->setSelected(false);
    m_lastPastePos += QPointF(10, 10);
  }
}
