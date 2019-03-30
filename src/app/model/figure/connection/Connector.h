#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QGraphicsPathItem>
#include <QList>

class Connection;

class Connector : public QGraphicsPathItem {
 public:
  Connector(QGraphicsItem *parent = nullptr);
  virtual ~Connector();

  Connector* create(QGraphicsItem* parent);
  QPointF centerScenePos();

  QString connectorType() const;

  void setDstConnection(Connection* dstConnection);
  void setSrcConnection(Connection* srcConnection);

  void removeDstConnection();
  void removeSrcConnection();

  QPointF centerOffset() const;


  QString name() const;
  void setName(const QString& name);

private:
  Connection* m_dstConnection = nullptr;
  Connection* m_srcConnection = nullptr;
  QString m_name;
};

#endif  // CONNECTOR_H
