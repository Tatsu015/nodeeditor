#include "Port.h"
#include "AbstractNode.h"
#include "Connection.h"
#include <QBrush>
#include <QPen>

const QColor Port::FILL_COLOR = QColor("#AAAAAA");
const QColor Port::LINE_COLOR = QColor("#AAAAAA");

Port::Port(IO io, uint32_t number, QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_portType("port"), m_parentNode(dynamic_cast<AbstractNode*>(parent)), m_io(io),
      m_number(number) {
  const static QBrush BLUSH = QBrush(FILL_COLOR);
  const static QPen PEN = QPen(LINE_COLOR, PEN_SIZE);
  setPen(PEN);
  setBrush(BLUSH);
  QPainterPath path;
  path.addRect(0, 0, WIDTH, HEIGHT);
  setPath(path);
}

Port::~Port() {
}

Port* Port::create(IO io, uint32_t number, QGraphicsItem* parent) {
  return new Port(io, number, parent);
}

QPointF Port::centerScenePos() {
  return sceneBoundingRect().center();
}

void Port::addConnection(Connection* connection) {
  m_connections << connection;
}

void Port::removeConnection(Connection* connection) {
  m_connections.removeOne(connection);
}

QList<Connection*> Port::connections() const {
  return m_connections;
}

IO Port::io() const {
  return m_io;
}

uint32_t Port::number() const {
  return m_number;
}

AbstractNode* Port::parentNode() const {
  return m_parentNode;
}

void Port::redraw() {
  foreach (Connection* connection, m_connections) { connection->redraw(); }
}

QString Port::portType() const {
  return m_portType;
}

QString Port::name() const {
  return m_name;
}

void Port::setName(const QString& name) {
  m_name = name;
}
