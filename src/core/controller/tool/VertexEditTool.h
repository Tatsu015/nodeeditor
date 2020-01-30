#ifndef VERTEXEDITTOOL_H
#define VERTEXEDITTOOL_H

#include "AbstractTool.h"

class VertexHandle;

const static QString TOOL_VERTEX_EDIT = "VertexEdit";

class VertexEditTool : public AbstractTool {
public:
  VertexEditTool();
  virtual ~VertexEditTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);

private:
  VertexHandle* m_editingVertexHandle = nullptr;
};

#endif // VERTEXEDITTOOL_H
