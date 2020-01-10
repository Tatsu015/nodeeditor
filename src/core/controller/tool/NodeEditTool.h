#ifndef NODEEDITTOOL_H
#define NODEEDITTOOL_H

#include "AbstractTool.h"
#include <QPointF>
#include <QStringList>

class QAction;
class AbstractNode;

const static QString TOOL_NODE_EDIT = "NodeEdit";

class NodeEditTool : public AbstractTool {
public:
  NodeEditTool();
  virtual ~NodeEditTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void keyPressEvent(Scene* scene, QKeyEvent* event);

  void setActiveNodeType(const QString& activeNodeType);

private:
  bool isSelectedNodesPressed(QPointF scenePos, Scene* scene);
  void drawGuideLine(Scene* scene);
  void drawTopGuideLineFromNearNodes(Scene* scene, AbstractNode* movingNode);
  void drawBottomGuideLineFromNearNodes(Scene* scene, AbstractNode* movingNode);
  void drawRightGuideLineFromNearNodes(Scene* scene, AbstractNode* movingNode);
  void drawLeftGuideLineFromNearNodes(Scene* scene, AbstractNode* movingNode);

private:
  bool m_isNodeMoving = false;
  QString m_activeNodeType = "";
  QList<AbstractNode*> m_selectedNodes;
};

#endif // NODEEDITTOOL_H
