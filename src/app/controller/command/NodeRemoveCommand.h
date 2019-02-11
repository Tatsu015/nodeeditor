#ifndef noderemoveCOMMAND_H
#define noderemoveCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class AbstractNode;
class Port;

class NodeRemoveCommand : public QUndoCommand {
private:
  struct NodeRemoveInfo
  {
    NodeRemoveInfo() {}
    AbstractNode* m_node = nullptr;
  };
 public:
  NodeRemoveCommand(Scene* scene, QList<AbstractNode*> nodes);
  virtual ~NodeRemoveCommand();

  virtual void redo();
  virtual void undo();

 private:
  Scene* m_scene = nullptr;
  AbstractNode* m_node = nullptr;
  QList<NodeRemoveInfo*> m_nodeRemoveInfos;
};

#endif  // noderemoveCOMMAND_H
