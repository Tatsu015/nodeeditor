#include "Port.h"
#include <QBrush>
#include <QPen>
#include "AbstractNode.h"
#include "Connection.h"

const QColor Port::FILL_COLOR = QColor("#AAAAAA");
const QColor Port::LINE_COLOR = QColor("#AAAAAA");

Port::Port(IO io, uint32_t number, QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_parentNode(dynamic_cast<AbstractNode*>(parent)), m_io(io), m_number(number) {
  const static QBrush BLUSH = QBrush(FILL_COLOR);
  const static QPen PEN = QPen(LINE_COLOR, PEN_SIZE);
  setPen(PEN);
  setBrush(BLUSH);
  QPainterPath path;
  path.addRect(0, 0, WIDTH, HEIGHT);
  setPath(path);
}

Port::~Port() {}

QPointF Port::centerScenePos() { return sceneBoundingRect().center(); }

void Port::addConnection(Connection* connection) { m_connections << connection; }

void Port::removeConnection(Connection* connection) { m_connections.removeOne(connection); }

QList<Connection*> Port::connections() const { return m_connections; }

IO Port::io() const { return m_io; }

uint32_t Port::number() const { return m_number; }

AbstractNode* Port::parentNode() const { return m_parentNode; }
