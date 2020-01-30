#include "VertexHandle.h"
#include "AbstractConnection.h"
#include <QBrush>
#include <QPen>

const static uint32_t WIDTH = 8;
const static uint32_t HEIGHT = 8;

VertexHandle::VertexHandle(QGraphicsItem* parent) : QGraphicsPathItem(parent) {

  const static QBrush BLUSH = QBrush(QColor(Qt::yellow));
  const static QPen PEN = QPen(QColor(Qt::darkYellow), 2);
  setBrush(BLUSH);
  setPen(PEN);

  QPainterPath path;
  path.addRect(-0.5 * WIDTH, -0.5 * HEIGHT, WIDTH, HEIGHT);
  path.closeSubpath();
  setPath(path);
}

VertexHandle::~VertexHandle() {
}

AbstractConnection* VertexHandle::connection() const {
  return dynamic_cast<AbstractConnection*>(parentItem());
}
