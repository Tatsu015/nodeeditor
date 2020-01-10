#ifndef CONNECTIONRECONNECTTOOL_H
#define CONNECTIONRECONNECTTOOL_H

#include "AbstractTool.h"
#include <QPointF>
#include <QStringList>

class QAction;
class AbstractNode;
class AbstractConnection;
class Port;

const static QString TOOL_CONNECTION_RECONNECT = "ConnectionReconnect";

class ConnectionReconnectTool : public AbstractTool {
public:
  ConnectionReconnectTool();
  virtual ~ConnectionReconnectTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);

private:
  void decideConnectToPort(Scene* scene, Port* lastEndPort, Port* targetEndPort);
  void decideConnectToConnector(Scene* scene, QPointF mouseReleaseScenePos, AbstractConnection* dstConnection);

  bool isOnConnectablePort(Scene* scene, QGraphicsSceneMouseEvent* event) const;
  bool isOnNode(Scene* scene, QGraphicsSceneMouseEvent* event) const;
  bool isOnConnecttableConnection(Scene* scene, QGraphicsSceneMouseEvent* event) const;

  void cancel();
  void reset();

private:
  AbstractNode* m_disconnectedNode = nullptr;
  AbstractConnection* m_connection = nullptr;
  Port* m_fixedPort = nullptr;
  Port* m_lastEndPort = nullptr;
  bool m_isReconnecting = false;
  bool m_isMoveStartPort = false;
};

#endif // CONNECTIONRECONNECTTOOL_H
