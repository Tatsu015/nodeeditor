#ifndef VERTEXHANDLE_H
#define VERTEXHANDLE_H

#include "Define.h"
#include <QGraphicsPathItem>

class AbstractConnection;

class VertexHandle : public QGraphicsPathItem {
public:
  VertexHandle(QGraphicsItem* parent = nullptr);
  virtual ~VertexHandle();

  AbstractConnection* connection() const;
};

#endif // VERTEXHANDLE_H
