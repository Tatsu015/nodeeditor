#ifndef ABSTRACTTOOL_H
#define ABSTRACTTOOL_H

class Scene;
class QGraphicsSceneMouseEvent;

class AbstractTool {
 public:
  AbstractTool();
  virtual ~AbstractTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) = 0;
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) = 0;
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) = 0;
  virtual void mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event) = 0;

  bool isUsing();

 protected:
  bool m_isUsing = false;
};

#endif  // ABSTRACTTOOL_H
