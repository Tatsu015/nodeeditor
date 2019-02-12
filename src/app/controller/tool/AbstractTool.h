#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

#include <QString>

class Scene;
class QGraphicsSceneMouseEvent;
class QKeyEvent;

class AbstractTool {
 public:
  AbstractTool(const QString& name);
  virtual ~AbstractTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) = 0;
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) = 0;
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) = 0;
  virtual void mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event) = 0;
  virtual void keyPressEvent(Scene* scene, QKeyEvent* event) = 0;
  virtual void keyReleaseEvent(Scene* scene, QKeyEvent* event) = 0;

  QString name() const;
  bool isUsing() const;
  bool isSelectable() const;

 protected:
  bool m_isUsing = false;
  bool m_isNodeSelectable = true;
  QString m_name = "";
};

#endif  // ABSTRACTTOOL_H
