#ifndef NODEREMOVECOMMAND_H
#define NODEREMOVECOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractNode;
class AbstractConnection;
class Port;
class Connector;

class NodeRemoveCommand : public QUndoCommand {
private:
  class ConnectionInfo {
  public:
    ConnectionInfo(AbstractConnection* connection, Port* startPort, Port* endPort);
    ~ConnectionInfo();

    void reconnect();

  private:
    AbstractConnection* m_connection = nullptr;
    Port* m_startPort = nullptr;
    Port* m_endPort = nullptr;
  };

public:
  NodeRemoveCommand(Scene* scene, Sheet* sheet, QList<AbstractNode*> nodes);
  virtual ~NodeRemoveCommand();

  virtual void redo();
  virtual void undo();

private:
  bool isStartNodeRemoved(const AbstractConnection* connection) const;
  bool isEndNodeRemoved(const AbstractConnection* connection) const;

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  QList<AbstractNode*> m_nodes;
  QList<AbstractConnection*> m_connections;
  QList<ConnectionInfo*> m_connectionInfos;
  //  QList<NodeRemoveInfo*> m_nodeRemoveInfos;
  //  QList<NodeConnectedInfo*> m_nodeConnectedInfos;
};

#endif // NODEREMOVECOMMAND_H
