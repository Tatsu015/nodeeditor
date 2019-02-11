#ifndef CONNECTIONCREATETOOL_H
#define CONNECTIONCREATETOOL_H

#include <QPointF>
#include "AbstractTool.h"

class Port;
class Connection;

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
  void addTmpConnection(Scene* scene, Port* startPort);
  void redrawTmpConnection(QPointF nowScenePos);
  void decideConnection(Scene* scene, Port* endPort);
  void removeTmpConnection(Scene* scene);

 private:
  Port* m_startPort = nullptr;
  Connection* m_tmpConnection = nullptr;
};

#endif  // CONNECTIONCREATETOOL_H
