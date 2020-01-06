#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QGraphicsPathItem>
#include <QList>

class AbstractConnection;

class Connector : public QGraphicsPathItem {
public:
  Connector(QGraphicsItem* parent = nullptr);
  virtual ~Connector();

  Connector* create(QGraphicsItem* parent);
  QPointF centerScenePos();

  QString connectorType() const;

  AbstractConnection* dstConnection() const;
  void setDstConnection(AbstractConnection* fromConnection);
  AbstractConnection* srcConnection() const;
  void setSrcConnection(AbstractConnection* srcConnection);

  void removeDstConnection();
  void removeSrcConnection();

  QPointF centerOffset() const;

  qreal xPosRate() const;
  void setXPosRate(const qreal& xPosRate);
  qreal yPosRate() const;
  void setYPosRate(const qreal& yPosRate);

private:
  AbstractConnection* m_dstConnection = nullptr;
  AbstractConnection* m_srcConnection = nullptr;
  QString m_name;
  qreal m_xPosRate;
  qreal m_yPosRate;
};

#endif // CONNECTOR_H
