#ifndef NODECREATETOOL_H
#define NODECREATETOOL_H

#include <QPointF>
#include <QStringList>
#include "AbstractTool.h"

class QAction;
class AbstractNode;

class NodeCreateTool : public AbstractTool {
 public:
  NodeCreateTool();
  virtual ~NodeCreateTool();

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

#endif  // NODECREATETOOL_H
