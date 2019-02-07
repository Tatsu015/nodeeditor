#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QGraphicsPathItem>

class Connector : public QGraphicsPathItem {
 public:
  Connector(QGraphicsItem *parent = nullptr);
  virtual ~Connector();

  void setPos(const QPointF pos);
};

#endif  // CONNECTOR_H
