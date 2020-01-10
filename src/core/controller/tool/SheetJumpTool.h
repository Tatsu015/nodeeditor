#ifndef SHEETJUMPTOOL_H
#define SHEETJUMPTOOL_H

#include "AbstractTool.h"

const static QString TOOL_SHEET_JUMP = "SheetJump";

class SheetJumpTool : public AbstractTool {
public:
  SheetJumpTool();
  virtual ~SheetJumpTool();

  //  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  //  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
};

#endif // SHEETJUMPTOOL_H
