#ifndef POLYLINEPolylineConnection_H
#define POLYLINEPolylineConnection_H

#include "AbstractConnection.h"

class PolylineConnection : public AbstractConnection {
public:
  PolylineConnection(QGraphicsItem* parent = nullptr);
  virtual ~PolylineConnection();

  virtual PolylineConnection* create(const QString& id);

  virtual void redraw();

  virtual QJsonObject toJsonObj();
};

#endif // POLYLINEPolylineConnection_H
