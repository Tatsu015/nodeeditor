#ifndef NodeEditTool_H
#define NodeEditTool_H

#include <QPointF>
#include <QStringList>
#include "AbstractTool.h"

class QAction;
class AbstractNode;

class NodeEditTool : public AbstractTool {
 public:
  NodeEditTool();
  virtual ~NodeEditTool();

  virtual void mousePressEvent(Scene *scene, QGraphicsSceneMouseEvent *event);
  virtual void mouseMoveEvent(Scene *scene, QGraphicsSceneMouseEvent *event);
  virtual void mouseReleaseEvent(Scene *scene, QGraphicsSceneMouseEvent *event);
  virtual void mouseDoubleClickEvent(Scene *scene, QGraphicsSceneMouseEvent *event);

  void setActiveNodeType(const QString &activeNodeType);

  QStringList nodeTypes() const;

 private:
  void drawGuideLine(Scene *scene);
  void drawTopGuideLineFromNearNodes(Scene *scene, AbstractNode *movingNode);
  void drawBottomGuideLineFromNearNodes(Scene *scene, AbstractNode *movingNode);
  void drawRightGuideLineFromNearNodes(Scene *scene, AbstractNode *movingNode);
  void drawLeftGuideLineFromNearNodes(Scene *scene, AbstractNode *movingNode);

 private:
  QStringList m_nodeTypes;
  QString m_activeNodeType = "";
};

#endif  // NodeEditTool_H
