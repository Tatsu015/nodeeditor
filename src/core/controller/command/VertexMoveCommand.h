#ifndef VERTEXMOVECOMMAND_H
#define VERTEXMOVECOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class VertexHandle;

class VertexMoveCommand : public QUndoCommand {
public:
  VertexMoveCommand(Scene* scene, Sheet* sheet, VertexHandle* movedVertexHandle, QPointF diff);
  virtual ~VertexMoveCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  VertexHandle* m_movedVertexHandle = nullptr;
  QPointF m_startScenePos;
  QPointF m_endScenePos;
  QPointF m_diff;
};

#endif // VERTEXMOVECOMMAND_H
