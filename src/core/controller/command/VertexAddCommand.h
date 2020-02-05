#ifndef VertexAddCommand_H
#define VertexAddCommand_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class VertexHandle;
class AbstractConnection;

class VertexAddCommand : public QUndoCommand {
public:
  VertexAddCommand(Scene* scene, Sheet* sheet, VertexHandle* addVertexHandle,AbstractConnection* targetConnection, int32_t index);
  virtual ~VertexAddCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  VertexHandle* m_addVertexHandle = nullptr;
  AbstractConnection* m_targetConnection = nullptr;
  int32_t m_areaIndex = 0;
};

#endif // VertexAddCommand_H
