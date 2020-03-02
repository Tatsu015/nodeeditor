#ifndef ELBOWCONNECTION_H
#define ELBOWCONNECTION_H

#include "AbstractConnection.h"
#include <QPointF>

class Port;
class Connector;

class ElbowConnection : public AbstractConnection {
public:
  ElbowConnection(QGraphicsItem* parent = nullptr);
  virtual ~ElbowConnection();

  virtual ElbowConnection* create(const QString& id);

  virtual QJsonObject toJsonObj();

protected:
  virtual QList<QPointF> createVertexes();
};

#endif // ELBOWCONNECTION_H
