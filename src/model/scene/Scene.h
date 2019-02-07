#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class AbstractNode;
class InNode;
class Connection;
class Connector;
class Port;

class Scene : public QGraphicsScene {
 public:
  Scene(QObject* parent = nullptr);
  virtual ~Scene();

  void autoSet();

  virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
  virtual void keyPressEvent(QKeyEvent* event);
  virtual void keyReleaseEvent(QKeyEvent* event);

  QList<AbstractNode*> nodes() const;
  void addNode(AbstractNode* node, QPointF scenePos);
  void removeNode(AbstractNode* node);

  QList<Connection*> connections() const;
  void addConnection(Connection* connection, Port* startPort);
  void addConnection(Connection* connection, Port* startPort, Port* endPort);
  void addConnection(const QString& startNodeName, int32_t startPortNumber, const QString& endNodeName, int32_t endPortNumber);
  void removeConnection(Connection* connection);

  bool existNode(QPointF pos);
  bool existPort(QPointF scenePos);
  Port* findPort(QPointF scenePos);

 private:
  void changeActiveTool(const QPointF nowScenePos);
  Port* findStartPort(QPointF scenePos);
  Port* findEndPort(QPointF scenePos);

  QList<AbstractNode*> findNodes(QPointF scenePos);
  AbstractNode* findNode(const QString& nodeName);

  Connection* findConnection(QPointF scenePos);

  bool existInNode(QPointF scenePos);

  void showConnector(QPointF scenePos);

 private:
  QList<AbstractNode*> m_nodes;
  QList<Connection*> m_connections;
  Connection* m_tmpConnection = nullptr;
  Connector* m_tmpConnector = nullptr;
  Port* m_startPort = nullptr;
  bool m_isControlPressed;
};

#endif  // SCENE_H
