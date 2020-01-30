#include "EdgeHandle.h"
#include "AbstractConnection.h"
#include <QBrush>
#include <QPen>

const static uint32_t WIDTH = 8;
const static uint32_t HEIGHT = 8;

EdgeHandle::EdgeHandle(Edge edge, QGraphicsItem* parent) : QGraphicsPathItem(parent), m_edge(edge) {

  const static QBrush BLUSH = QBrush(QColor(Qt::red));
  const static QPen PEN = QPen(QColor(Qt::darkRed), 2);
  setBrush(BLUSH);
  setPen(PEN);

  QPainterPath path;
  path.addRect(-0.5 * WIDTH, -0.5 * HEIGHT, WIDTH, HEIGHT);
  path.closeSubpath();
  setPath(path);
}

EdgeHandle::~EdgeHandle() {
}

Edge EdgeHandle::edge() const {
  return m_edge;
}

AbstractConnection* EdgeHandle::connection() const {
  return dynamic_cast<AbstractConnection*>(parentItem());
}
