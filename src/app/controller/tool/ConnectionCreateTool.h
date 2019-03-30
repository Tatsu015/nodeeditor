#ifndef CONNECTIONCREATETOOL_H
#define CONNECTIONCREATETOOL_H

#include <QPointF>
#include "AbstractTool.h"

class Port;
class Connection;
class TmpConnection;
class Connector;

class ConnectionCreateTool : public AbstractTool {
 public:
  ConnectionCreateTool();
  virtual ~ConnectionCreateTool();

  virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event);
  virtual void keyPressEvent(Scene* scene, QKeyEvent* event);
  virtual void keyReleaseEvent(Scene* scene, QKeyEvent* event);

 private:
  void decideConnectToPort(Scene* scene, Port* endPort);
  void decideConnectToConnector(Scene* scene);

  void addTmpConnector(Scene* scene, Port* startPort);
  void redrawTmpConnector(QPointF nowScenePos);
  void decideConnector(Scene* scene, Port* endPort);
  void removeTmpConnector(Scene* scene);

  bool canConnect(Scene *scene, QGraphicsSceneMouseEvent *event) const;
  bool canConnectToPort(Scene *scene, QGraphicsSceneMouseEvent *event) const;
  bool canConnectToConnector(Scene *scene, QGraphicsSceneMouseEvent *event) const;

 private:
  Port* m_startPort = nullptr;
  TmpConnection* m_tmpConnection = nullptr;
  Connector* m_tmpConnector = nullptr;
};

#endif  // CONNECTIONCREATETOOL_H
