#include "Port.h"
#include "AbstractNode.h"
#include "Connection.h"
#include "float.h"
#include <QBrush>
#include <QPen>

const QColor Port::LINE_FILL_COLOR = QColor("#AAAAAA");
const QColor Port::LINE_COLOR = QColor("#AAAAAA");
const QColor Port::ELLIPSE_FILL_COLOR = QColor("#666666");
const QColor Port::ELLIPSE_COLOR = QColor("#AAAAAA");

Port::Port(IO io, uint32_t number, QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_portType("port"), m_parentNode(dynamic_cast<AbstractNode*>(parent)), m_io(io),
      m_number(number) {
  const static QBrush BLUSH = QBrush(LINE_FILL_COLOR);
  const static QPen PEN = QPen(LINE_COLOR, LINE_PEN_SIZE);
  setPen(PEN);
  setBrush(BLUSH);
  QPainterPath path;
  path.addRect(0, 0, LINE_WIDTH, LINE_HEIGHT);
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

QPointF Port::endOfPortPos() {
  if (Output == m_io) {
    return (sceneBoundingRect().topRight() + sceneBoundingRect().bottomRight()) * 0.5;
  } else if (Input == m_io) {
    return (sceneBoundingRect().topLeft() + sceneBoundingRect().bottomLeft()) * 0.5;
  }
  return centerScenePos();
}

QPointF Port::endOfNodePos() {
  if (Input == m_io) {
    return (sceneBoundingRect().topRight() + sceneBoundingRect().bottomRight()) * 0.5;
  } else if (Output == m_io) {
    return (sceneBoundingRect().topLeft() + sceneBoundingRect().bottomLeft()) * 0.5;
  }
  return centerScenePos();
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

bool Port::canConnect() const {
  if (m_maxConnectableCount <= m_connections.count()) {
    return false;
  }
  return true;
}

void Port::invert() {
  m_isInvert = !m_isInvert;
  if (m_isInvert) {
    const static QBrush BLUSH = QBrush(ELLIPSE_FILL_COLOR);
    const static QPen PEN = QPen(ELLIPSE_COLOR, ELLIPSE_PEN_SIZE);
    setPen(PEN);
    setBrush(BLUSH);
    QPainterPath path;
    path.addEllipse(0, -0.5 * ELLIPSE_RADIUS, ELLIPSE_RADIUS, ELLIPSE_RADIUS);
    setPath(path);
  } else {
    const static QBrush BLUSH = QBrush(LINE_FILL_COLOR);
    const static QPen PEN = QPen(LINE_COLOR, LINE_PEN_SIZE);
    setPen(PEN);
    setBrush(BLUSH);
    QPainterPath path;
    path.addRect(0, 0, LINE_WIDTH, LINE_HEIGHT);
    setPath(path);
  }
}

bool Port::isInvert() const {
  return m_isInvert;
}
