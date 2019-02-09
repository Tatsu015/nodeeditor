#ifndef ConnectionAddCOMMAND_H
#define ConnectionAddCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Connection;
class Port;

class ConnectionAddCommand : public QUndoCommand {
 public:
  ConnectionAddCommand(Scene* scene, Connection* connection, Port* addScenePos, Port* endPort);
  virtual ~ConnectionAddCommand();

  virtual void redo();
  virtual void undo();

 private:
  Scene* m_scene = nullptr;
  Connection* m_connection = nullptr;
  Port* m_startPort = nullptr;
  Port* m_endPort = nullptr;
};

#endif  // ConnectionAddCOMMAND_H
