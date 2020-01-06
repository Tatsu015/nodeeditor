#ifndef PortRemoveCOMMAND_H
#define PortRemoveCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractNode;
class Port;
class AbstractConnection;

class PortRemoveCommand : public QUndoCommand {
private:
  struct ConnectionInfo {
    AbstractConnection* m_connection = nullptr;
    Port* m_oppositeSidePort;
  };

public:
  PortRemoveCommand(Scene* scene, Sheet* sheet, AbstractNode* node, Port* port);
  virtual ~PortRemoveCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  AbstractNode* m_node = nullptr;
  Port* m_port = nullptr;
  QList<ConnectionInfo*> m_connectionInfos;
};

#endif // PortRemoveCOMMAND_H
