#ifndef ConnectionReconnectTool_H
#define ConnectionReconnectTool_H

#include "AbstractTool.h"
#include <QPointF>
#include <QStringList>

class QAction;
class AbstractNode;
class Connection;
class Port;

class ConnectionReconnectTool : public AbstractTool {
public:
  ConnectionReconnectTool();
  virtual ~ConnectionReconnectTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);

private:
  void decideConnectToPort(Scene* scene, Port* lastEndPort, Port* targetEndPort);
  void decideConnectToConnector(Scene* scene, QPointF mouseReleaseScenePos, Connection* dstConnection);

  bool isOnConnectablePort(Scene* scene, QGraphicsSceneMouseEvent* event) const;
  bool isOnNode(Scene* scene, QGraphicsSceneMouseEvent* event) const;
  bool isOnConnecttableConnection(Scene* scene, QGraphicsSceneMouseEvent* event) const;

  void cancel();
  void reset();

private:
  AbstractNode* m_disconnectedNode = nullptr;
  Connection* m_connection = nullptr;
  Port* m_fixedPort = nullptr;
  Port* m_lastEndPort = nullptr;
  bool m_isReconnecting = false;
  bool m_isMoveStartPort = false;
};

#endif // ConnectionReconnectTool_H