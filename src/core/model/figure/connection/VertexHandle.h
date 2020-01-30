#ifndef VertexHANDLE_H
#define VertexHANDLE_H

#include "Define.h"
#include <QGraphicsPathItem>

class AbstractConnection;

class VertexHandle : public QGraphicsPathItem {
public:
  VertexHandle(QGraphicsItem* parent = nullptr);
  virtual ~VertexHandle();

  AbstractConnection* connection() const;
};

#endif // VertexHANDLE_H
