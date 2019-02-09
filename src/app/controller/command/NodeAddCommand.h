#ifndef NODEADDCOMMAND_H
#define NODEADDCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class AbstractNode;

class NodeAddCommand : public QUndoCommand {
 public:
  NodeAddCommand(Scene* scene, AbstractNode* node, QPointF addScenePos);
  virtual ~NodeAddCommand();

  virtual void redo();
  virtual void undo();

 private:
  Scene* m_scene = nullptr;
  AbstractNode* m_node = nullptr;
  QPointF m_addScenePos;
};

#endif  // NODEADDCOMMAND_H
