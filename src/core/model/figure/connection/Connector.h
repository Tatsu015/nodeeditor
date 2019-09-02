#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QGraphicsPathItem>
#include <QList>

class Connection;

class Connector : public QGraphicsPathItem {
public:
  Connector(QGraphicsItem* parent = nullptr);
  virtual ~Connector();

  Connector* create(QGraphicsItem* parent);
  QPointF centerScenePos();

  QString connectorType() const;

  Connection* dstConnection() const;
  void setDstConnection(Connection* fromConnection);
  Connection* srcConnection() const;
  void setSrcConnection(Connection* srcConnection);

  void removeDstConnection();
  void removeSrcConnection();

  QPointF centerOffset() const;

  qreal xPosRate() const;
  void setXPosRate(const qreal& xPosRate);
  qreal yPosRate() const;
  void setYPosRate(const qreal& yPosRate);

private:
  Connection* m_dstConnection = nullptr;
  Connection* m_srcConnection = nullptr;
  QString m_name;
  qreal m_xPosRate;
  qreal m_yPosRate;
};

#endif // CONNECTOR_H
