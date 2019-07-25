#ifndef ConnectToConnectorCommand_H
#define ConnectToConnectorCommand_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Connection;
class Port;
class Connector;

class ConnectToConnectorCommand : public QUndoCommand {
public:
  ConnectToConnectorCommand(Scene* scene, Connection* connection, Port* addScenePos, Connector* endConnector,
                            Connection* dstConnection);
  virtual ~ConnectToConnectorCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Connection* m_connection = nullptr;
  Port* m_startPort = nullptr;
  Connector* m_endConnector = nullptr;
  Connection* m_dstConnection = nullptr;
};

#endif // ConnectToConnectorCommand_H
