#ifndef noderemoveCOMMAND_H
#define noderemoveCOMMAND_H

#include <QPointF>
#include <QUndoCommand>

class Scene;
class AbstractNode;
class Connection;
class Port;

class NodeRemoveCommand : public QUndoCommand {
 private:
  struct NodeConnectedInfo {
    Connection* m_connection = nullptr;
    QString m_startNodeName;
    uint32_t m_startPortNumber;
    QString m_endNodeName;
    uint32_t m_endPortNumber;
  };
  struct ConnectionInfo {
    Connection* m_connection = nullptr;
    QString m_startNodeName;
    uint32_t m_startPortNumber;
    QString m_endNodeName;
    uint32_t m_endPortNumber;
  };
  struct NodeRemoveInfo {
    AbstractNode* m_node = nullptr;
    QList<ConnectionInfo*> m_connectionInfos;
  };

 public:
  NodeRemoveCommand(Scene* scene, QList<AbstractNode*> nodes);
  virtual ~NodeRemoveCommand();

  virtual void redo();
  virtual void undo();

 private:
  Scene* m_scene = nullptr;
  AbstractNode* m_node = nullptr;
  QList<NodeRemoveInfo*> m_nodeRemoveInfos;
  QList<NodeConnectedInfo*> m_nodeConnectedInfos;
};

#endif  // noderemoveCOMMAND_H
