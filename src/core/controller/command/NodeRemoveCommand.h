#ifndef noderemoveCOMMAND_H
#define noderemoveCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class Sheet;
class AbstractNode;
class Connection;
class Port;
class Connector;

class NodeRemoveCommand : public QUndoCommand {
private:
  struct NodeConnectedInfo {
    Connection* m_connection = nullptr;
    QString m_startNodeName;
    uint32_t m_startPortNumber;
    QString m_endNodeName;
    uint32_t m_endPortNumber;
  };
  struct ConnectorInfo {
    Connector* m_connector = nullptr;
    Connection* m_parentConnection = nullptr;
    Connection* m_dstConnection = nullptr;
  };
  struct ConnectionInfo {
    Connection* m_connection = nullptr;
    QString m_startNodeName;
    uint32_t m_startPortNumber;
    QString m_endNodeName;
    uint32_t m_endPortNumber;
    ConnectorInfo m_endConnectorInfo;
  };
  struct NodeRemoveInfo {
    AbstractNode* m_node = nullptr;
    QList<ConnectionInfo*> m_connectionInfos;
  };

public:
  NodeRemoveCommand(Scene* scene, Sheet* sheet, QList<AbstractNode*> nodes);
  virtual ~NodeRemoveCommand();

  virtual void redo();
  virtual void undo();

private:
  Scene* m_scene = nullptr;
  Sheet* m_sheet = nullptr;
  AbstractNode* m_node = nullptr;
  QList<NodeRemoveInfo*> m_nodeRemoveInfos;
  QList<NodeConnectedInfo*> m_nodeConnectedInfos;
};

#endif // noderemoveCOMMAND_H
