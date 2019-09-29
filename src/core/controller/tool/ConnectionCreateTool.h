#ifndef CONNECTIONCREATETOOL_H
#define CONNECTIONCREATETOOL_H

#include "AbstractTool.h"
#include <QPointF>

class Port;
class Connection;
class Connector;

class ConnectionCreateTool : public AbstractTool {
public:
  ConnectionCreateTool();
  virtual ~ConnectionCreateTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void keyPressEvent(Scene* scene, QKeyEvent* event);

private:
  void decideConnectToPort(Scene* scene, Port* endPort);
  void decideConnectToConnector(Scene* scene, QPointF mouseReleaseScenePos, Connection* dstConnection);

  void addTmpConnector(Scene* scene, Port* startPort);
  void redrawTmpConnector(QPointF nowScenePos);
  void decideConnector(Scene* scene, Port* endPort);
  void removeTmpConnector(Scene* scene);

  bool isOnConnectablePort(Scene* scene, QGraphicsSceneMouseEvent* event) const;
  bool isOnNode(Scene* scene, QGraphicsSceneMouseEvent* event) const;
  bool isOnConnecttableConnection(Scene* scene, QGraphicsSceneMouseEvent* event) const;

  void cancel();
  void reset();

private:
  Port* m_startPort = nullptr;
  Connection* m_tmpConnection = nullptr;
};

#endif // CONNECTIONCREATETOOL_H
