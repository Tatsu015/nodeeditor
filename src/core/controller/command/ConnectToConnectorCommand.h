#ifndef ConnectToConnectorCommand_H
#define ConnectToConnectorCommand_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractConnection;
class Port;
class Connector;

class ConnectToConnectorCommand : public QUndoCommand {
public:
  ConnectToConnectorCommand(Scene* scene, Sheet* sheet, AbstractConnection* connection, Port* addScenePos,
                            Connector* endConnector, AbstractConnection* dstConnection, QList<QPointF> vertexes);
  virtual ~ConnectToConnectorCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  AbstractConnection* m_connection = nullptr;
  Port* m_startPort = nullptr;
  Connector* m_endConnector = nullptr;
  AbstractConnection* m_dstConnection = nullptr;
  QList<QPointF> m_vertexes;
};

#endif // ConnectToConnectorCommand_H
