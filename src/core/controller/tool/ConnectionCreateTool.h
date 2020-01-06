#ifndef CONNECTIONCREATETOOL_H
#define CONNECTIONCREATETOOL_H

#include "AbstractTool.h"
#include <QPointF>

class Port;
class AbstractConnection;
class Connector;

class ConnectionCreateTool : public AbstractTool {
public:
  ConnectionCreateTool();
  virtual ~ConnectionCreateTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void keyPressEvent(Scene* scene, QKeyEvent* event);

  void setActiveConnectionType(const QString& activeConnectionType);

private:
  void decideConnectToPort(Scene* scene, Port* endPort, QList<QPointF> vertexes);
  void decideConnectToConnector(Scene* scene, QPointF mouseReleaseScenePos, AbstractConnection* dstConnection,
                                QList<QPointF> vertexes);

  bool isOnConnectablePort(Scene* scene, QGraphicsSceneMouseEvent* event) const;
  bool isOnNode(Scene* scene, QGraphicsSceneMouseEvent* event) const;
  bool isOnConnecttableConnection(Scene* scene, QGraphicsSceneMouseEvent* event) const;

  void cancel();
  void reset();

private:
  QString m_activeConnectionType = "";
  Port* m_startPort = nullptr;
  AbstractConnection* m_tmpConnection = nullptr;
};

#endif // CONNECTIONCREATETOOL_H
