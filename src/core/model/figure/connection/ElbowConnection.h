#ifndef ELBOWCONNECTION_H
#define ELBOWCONNECTION_H

#include "AbstractConnection.h"

class Port;
class Connector;

class ElbowConnection : public AbstractConnection {
public:
  ElbowConnection(QGraphicsItem* parent = nullptr);
  virtual ~ElbowConnection();

  virtual ElbowConnection* create(const QString& id);

  virtual void redraw();

  virtual QJsonObject toJsonObj();
};

#endif // ELBOWCONNECTION_H
