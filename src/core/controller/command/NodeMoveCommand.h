#ifndef NodeMoveCommand_H
#define NodeMoveCommand_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class AbstractNode;

class NodeMoveCommand : public QUndoCommand {
private:
  struct NodeMoveInfo {
    NodeMoveInfo() {
    }
    AbstractNode* m_node = nullptr;
    QPointF m_startScenePos;
    QPointF m_endScenePos;
  };

public:
  NodeMoveCommand(Scene* scene, QList<AbstractNode*> nodes, QPointF diff);
  virtual ~NodeMoveCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  QList<NodeMoveInfo*> m_nodeMovenfos;
  QPointF m_diff;
};

#endif // NodeMoveCommand_H
