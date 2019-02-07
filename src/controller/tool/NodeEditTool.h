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
  QStringList m_nodeTypes;
  QString m_activeNodeType = "";
};

#endif  // NodeEditTool_H
