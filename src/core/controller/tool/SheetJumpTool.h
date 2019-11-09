#ifndef SheetJumpTool_H
#define SheetJumpTool_H

#include "AbstractTool.h"

class SheetJumpTool : public AbstractTool {
public:
  SheetJumpTool();
  virtual ~SheetJumpTool();

  //  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  //  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
};

#endif // SheetJumpTool_H
