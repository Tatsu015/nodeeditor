#ifndef POLYLINECONNECTION_H
#define POLYLINECONNECTION_H

#include "AbstractConnection.h"

const static QString CONNECTION_POLYLINE = "Polyline";

class PolylineConnection : public AbstractConnection {
public:
  PolylineConnection(QGraphicsItem* parent = nullptr);
  virtual ~PolylineConnection();

  virtual PolylineConnection* create(const QString& id);

  virtual QJsonObject toJsonObj();

protected:
  virtual void doRedraw();
};

#endif // POLYLINECONNECTION_H
