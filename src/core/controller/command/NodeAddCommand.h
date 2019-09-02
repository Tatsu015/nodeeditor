#ifndef NODEADDCOMMAND_H
#define NODEADDCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractNode;

class NodeAddCommand : public QUndoCommand {
public:
  NodeAddCommand(Scene* scene, Sheet* sheet, AbstractNode* node, QPointF addScenePos);
  virtual ~NodeAddCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  AbstractNode* m_node = nullptr;
  QPointF m_addScenePos;
};

#endif // NODEADDCOMMAND_H
