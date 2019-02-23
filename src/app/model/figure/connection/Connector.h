#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QGraphicsPathItem>
#include <QList>

class Connection;

class Connector : public QGraphicsPathItem {
 public:
  Connector(QGraphicsItem *parent = nullptr);
  virtual ~Connector();

  void setPos(const QPointF pos);

  void setDstConnection(Connection* dstConnection);
  void setSrcConnection(Connection* srcConnection);

private:
  Connection* m_dstConnection = nullptr;
  Connection* m_srcConnection = nullptr;
};

#endif  // CONNECTOR_H
