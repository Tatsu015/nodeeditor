#ifndef EDGEHANDLE_H
#define EDGEHANDLE_H

#include "Define.h"
#include <QGraphicsPathItem>

class AbstractConnection;

class EdgeHandle : public QGraphicsPathItem {
public:
  EdgeHandle(Edge edge, QGraphicsItem* parent = nullptr);
  virtual ~EdgeHandle();

  Edge edge() const;
  AbstractConnection* connection() const;

private:
  Edge m_edge = None;
};

#endif // EDGEHANDLE_H
