#ifndef noderemoveCOMMAND_H
#define noderemoveCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class AbstractNode;
class Port;

class NodeRemoveCommand : public QUndoCommand {
 public:
  NodeRemoveCommand(Scene* scene, AbstractNode* node, QPointF addScenePos);
  virtual ~NodeRemoveCommand();

  virtual void redo();
  virtual void undo();

 private:
  Scene* m_scene = nullptr;
  AbstractNode* m_node = nullptr;
  QPointF m_addScenePos;
};

#endif  // noderemoveCOMMAND_H
