#ifndef NODEREPLACECOMMAND_H
#define NODEREPLACECOMMAND_H

#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractNode;

class NodeReplaceCommand : public QUndoCommand {

public:
  NodeReplaceCommand(Scene* scene, Sheet* sheet, AbstractNode* srcNode, AbstractNode* dstNode);
  virtual ~NodeReplaceCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  AbstractNode* m_srcNode = nullptr;
  AbstractNode* m_dstNode = nullptr;
};

#endif // NODEREPLACECOMMAND_H
