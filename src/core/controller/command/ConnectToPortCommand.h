#ifndef ConnectToPortCommand_H
#define ConnectToPortCommand_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class Connection;
class Port;
class Connector;

class ConnectToPortCommand : public QUndoCommand {
public:
  ConnectToPortCommand(Scene* scene, Sheet* sheet, Connection* connection, Port* startPort, Port* endPort);
  virtual ~ConnectToPortCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  Connection* m_connection = nullptr;
  Port* m_startPort = nullptr;
  Port* m_endPort = nullptr;
};

#endif // ConnectToPortCommand_H
