#include "Port.h"
#include "AbstractConnection.h"
#include "AbstractNode.h"
#include "ProjectKeyDefine.h"
#include "SystemConfig.h"
#include "float.h"
#include <QBrush>
#include <QDebug>
#include <QPen>

Port::Port(IO io, uint32_t number, QGraphicsItem* parent, bool isInvert, bool isRemovable)
    : QGraphicsPathItem(parent), m_portType("port"), m_parentNode(dynamic_cast<AbstractNode*>(parent)), m_io(io),
      m_number(number), m_isInvert(isInvert), m_isRemovable(isRemovable) {
  const static QBrush BLUSH = QBrush(QColor(systemConfig(SystemConfig::nodeLineColor).toString()));
  const static QPen PEN = QPen(QColor(systemConfig(SystemConfig::nodeLineColor).toString()), LINE_PEN_SIZE);
  setPen(PEN);
  setBrush(BLUSH);
  QPainterPath path;
  path.addRect(0, (HEIGHT - LINE_HEIGHT) * 0.5, LINE_WIDTH, LINE_HEIGHT);
  setPath(path);

  invert(m_isInvert);
}

Port::~Port() {
}

QRectF Port::boundingRect() const {
  return QRectF(0, 0, WIDTH, HEIGHT);
}

Port* Port::create(IO io, uint32_t number, QGraphicsItem* parent, bool isInvert, bool isRemovable) {
  return new Port(io, number, parent, isInvert, isRemovable);
}

QPointF Port::centerScenePos() {
  return sceneBoundingRect().center();
}

QPointF Port::endOfPortPos() {
  if (Output == m_io) {
    return QPointF(sceneBoundingRect().right(), sceneBoundingRect().center().y());
  } else if (Input == m_io) {
    return QPointF(sceneBoundingRect().left(), sceneBoundingRect().center().y());
  }
  return centerScenePos();
}

QPointF Port::endOfNodePos() {
  if (Input == m_io) {
    return QPointF(sceneBoundingRect().right(), sceneBoundingRect().center().y());
  } else if (Output == m_io) {
    return QPointF(sceneBoundingRect().left(), sceneBoundingRect().center().y());
  }
  return centerScenePos();
}

void Port::addConnection(AbstractConnection* connection) {
  m_connections << connection;
}

void Port::removeConnection(AbstractConnection* connection) {
  m_connections.removeOne(connection);
}

QList<AbstractConnection*> Port::connections() const {
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
  foreach (AbstractConnection* connection, m_connections) { connection->redraw(); }
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

void Port::invert(const bool isInvert) {
  m_isInvert = isInvert;
  if (m_isInvert) {
    const static QBrush BLUSH = QBrush(QColor(systemConfig(SystemConfig::nodeFillColor).toString()));
    const static QPen PEN = QPen(QColor(systemConfig(SystemConfig::nodeLineColor).toString()), ELLIPSE_PEN_SIZE);
    setPen(PEN);
    setBrush(BLUSH);
    QPainterPath path;
    path.addEllipse(0, (HEIGHT - ELLIPSE_RADIUS) * 0.5, ELLIPSE_RADIUS, ELLIPSE_RADIUS);
    setPath(path);
  } else {
    const static QBrush BLUSH = QBrush(QColor(systemConfig(SystemConfig::nodeLineColor).toString()));
    const static QPen PEN = QPen(QColor(systemConfig(SystemConfig::nodeLineColor).toString()), LINE_PEN_SIZE);
    setPen(PEN);
    setBrush(BLUSH);
    QPainterPath path;
    path.addRect(0, (HEIGHT - LINE_HEIGHT) * 0.5, LINE_WIDTH, LINE_HEIGHT);
    setPath(path);
  }
}

bool Port::isInvert() const {
  return m_isInvert;
}

bool Port::isRemovable() const {
  return m_isRemovable;
}

QJsonObject Port::toJsonObj() {
  QJsonObject jsonObj;
  jsonObj[JSON_PORT_NUMBER] = static_cast<int32_t>(m_number);
  jsonObj[JSON_PORT_IO] = static_cast<int32_t>(m_io);
  jsonObj[JSON_PORT_INVERTED] = m_isInvert;

  return jsonObj;
}
