#ifndef PORTADDCOMMAND_H
#define PORTADDCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractNode;
class Port;

class PortAddCommand : public QUndoCommand {
public:
  PortAddCommand(Scene* scene, Sheet* sheet, AbstractNode* node, Port* port);
  virtual ~PortAddCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  AbstractNode* m_node = nullptr;
  Port* m_port = nullptr;
};

#endif // PORTADDCOMMAND_H
