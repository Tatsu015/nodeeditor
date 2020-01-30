#ifndef VertexRemoveCommand_H
#define VertexRemoveCommand_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class VertexHandle;
class AbstractConnection;

class VertexRemoveCommand : public QUndoCommand {
public:
  VertexRemoveCommand(Scene* scene, Sheet* sheet, VertexHandle* removedVertexHandle);
  virtual ~VertexRemoveCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  VertexHandle* m_removedVertexHandle = nullptr;
  AbstractConnection* m_targetConnection = nullptr;
  int32_t m_index = 0;
};

#endif // VertexRemoveCommand_H
