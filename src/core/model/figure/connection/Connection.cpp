#include "Connection.h"
#include "Connector.h"
#include "Define.h"
#include "Port.h"
#include "SystemConfig.h"
#include <QPen>
#include <QUuid>

const uint32_t Connection::PEN_SIZE = 3;

Connection::Connection(QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_id(QUuid::createUuid().toString()), m_connectionType(CONNECTION) {
  setPen(QPen(QColor(systemConfig(SystemConfig::connectionColor).toString()), PEN_SIZE));
}

Connection::~Connection() {
}

Connection* Connection::create() {
  return create(QUuid::createUuid().toString());
}

Connection* Connection::create(const QString& id) {
  Connection* connection = new Connection();
  connection->m_id = id;
  return connection;
}

QPointF Connection::startPos() const {
  return m_startPos;
}

void Connection::setStartPos(const QPointF& startPos) {
  m_startPos = startPos;
  redraw();
}

QPointF Connection::endPos() const {
  return m_endPos;
}

void Connection::setEndPos(const QPointF& endPos) {
  m_endPos = endPos;
  redraw();
}

void Connection::setStartPort(Port* startPort) {
  m_startPort = startPort;
  m_startPos = startPort->endOfPortPos();
  redraw();
}

void Connection::setEndPort(Port* endPort) {
  m_endPort = endPort;
  m_endPos = endPort->endOfPortPos();
  redraw();
}
#include <QDebug>
void Connection::redraw() {
  // m_startPos and m_endPos need to change. Because port and connector position updated by QGraphicsItem::ItemMove, But
  // m_startPos and m_endPos cannot update!
  if (m_startPort) {
    m_startPos = m_startPort->endOfPortPos();
  }
  if (m_endPort) {
    m_endPos = m_endPort->endOfPortPos();
  }
  if (m_endConnector) {
    m_endPos = m_endConnector->centerScenePos();
  }

  QPointF elbowPos = (m_startPos + m_endPos) * 0.5;

  foreach (Connector* connector, m_branchConnectors) {
    QPointF pos = m_endPos - m_startPos;
    QPointF connectorPos(m_startPos.x() + pos.x() * connector->xPosRate(),
                         m_startPos.y() + pos.y() * connector->yPosRate());
    connectorPos += connector->centerOffset();
    connector->setPos(connectorPos);
    // redraw connector connected connection
    connector->srcConnection()->redraw();
  }

  QPainterPath path;
  QPointF elbow1(elbowPos.x(), m_startPos.y());
  QPointF elbow2(elbowPos.x(), m_endPos.y());
  path.moveTo(m_startPos);
  path.lineTo(elbow1);
  path.lineTo(elbow2);
  path.lineTo(m_endPos);
  path.lineTo(elbow2);
  path.lineTo(elbow1);
  path.closeSubpath();
  setPath(path);
}

void Connection::redraw(Port* startPort, Port* endPort) {
  m_startPort = startPort;
  m_endPort = endPort;
  redraw();
}

void Connection::redraw(Port* startPort, QPointF endScenePos) {
  m_startPort = startPort;
  m_endPos = endScenePos;
  redraw();
}

Port* Connection::startPort() const {
  return m_startPort;
}

Port* Connection::endPort() const {
  return m_endPort;
}

void Connection::removeStartPort() {
  m_startPort = nullptr;
}

void Connection::removeEndPort() {
  m_endPort = nullptr;
}

Port* Connection::oppositeSidePort(Port* port) {
  if (port == m_startPort) {
    return m_endPort;
  } else {
    return m_startPort;
  }
}

QVector<QPointF> Connection::points() const {
  QVector<QPointF> elements;
  int32_t elementCount = path().elementCount();
  for (int i = 0; i < elementCount; ++i) {
    QPainterPath::Element element = path().elementAt(i);
    if (!elements.contains(element)) {
      elements << element;
    }
  }
  return elements;
}

int32_t Connection::areaIndex(QPointF pos, QSizeF searchSize) const {
  QVector<QPointF> elements = points();
  for (int i = 0; i < elements.count() - 1; ++i) {
    QRectF r(elements[i], elements[i + 1]);
    QRectF dmg;
    if (0 == r.width()) {
      dmg = QRectF(r.x() - searchSize.width(), r.y(), 2 * searchSize.width(), r.height());
    } else {
      dmg = QRectF(r.x(), r.y() - searchSize.height(), r.width(), 2 * searchSize.height());
    }
    if (dmg.contains(pos)) {
      return i;
    }
  }
  return -1;
}

QPointF Connection::closeCenter(QPointF pos, QSizeF searchSize) {
  QVector<QPointF> elements = points();
  for (int i = 0; i < elements.count() - 1; ++i) {
    QRectF r(elements[i], elements[i + 1]);
    QRectF dmg;
    QPointF rrr;
    if (0 == r.width()) {
      dmg = QRectF(r.x() - searchSize.width(), r.y(), 2 * searchSize.width(), r.height());
      rrr.setX(r.x());
      rrr.setY(pos.y());
    } else {
      dmg = QRectF(r.x(), r.y() - searchSize.height(), r.width(), 2 * searchSize.height());
      rrr.setX(pos.x());
      rrr.setY(r.y());
    }
    if (dmg.contains(pos)) {
      return rrr;
    }
  }
  return QPointF();
}

Connection::Direction Connection::direction(QPointF pos, QSizeF searchSize) const {
  QVector<QPointF> elements = points();
  for (int i = 0; i < elements.count() - 1; ++i) {
    QRectF r(elements[i], elements[i + 1]);
    QRectF dmg;
    Connection::Direction direction = Vertical;
    if (0 == r.width()) {
      dmg = QRectF(r.x() - searchSize.width(), r.y(), 2 * searchSize.width(), r.height());
      direction = Vertical;
    } else {
      dmg = QRectF(r.x(), r.y() - searchSize.height(), r.width(), 2 * searchSize.height());
      direction = Horizon;
    }
    if (dmg.contains(pos)) {
      return direction;
    }
  }
  return Other;
}

Connection::Edge Connection::whichEdge(Port* port) {
  if (m_startPort == port) {
    return Start;
  } else if (m_endPort == port) {
    return End;
  } else {
    return None;
  }
}

void Connection::addBranchConnector(Connector* connector) {
  connector->setParentItem(this);
  m_branchConnectors << connector;
}

void Connection::removeBranchConnector(Connector* connector) {
  m_branchConnectors.removeOne(connector);
}

QList<Connector*> Connection::branchConnectors() const {
  return m_branchConnectors;
}

QString Connection::name() const {
  return m_name;
}

void Connection::setName(const QString& name) {
  m_name = name;
}

QString Connection::connectionType() const {
  return m_connectionType;
}

QString Connection::id() const {
  return m_id;
}

void Connection::changeConnectionStyle(const Connection::ConnectionStyle style) {
  const QColor CREATING_LINE_COLOR = QColor(systemConfig(SystemConfig::creatingConnectionColor).toString());
  const QColor DECIDED_LINE_COLOR = QColor(systemConfig(SystemConfig::decidedConnectionColor).toString());

  if (Connecting == style) {
    setPen(QPen(CREATING_LINE_COLOR, PEN_SIZE, Qt::DotLine));
  } else if (Connectable == style) {
    setPen(QPen(DECIDED_LINE_COLOR, PEN_SIZE, Qt::SolidLine));
  } else {
    setPen(QPen(QColor(systemConfig(SystemConfig::connectionColor).toString()), PEN_SIZE, Qt::SolidLine));
  }
}

// todo node dependency want to remove
// node will change to port.
#include "AbstractNode.h"
QJsonObject Connection::toJsonObj() {
  QJsonObject connectionJsonObj;
  connectionJsonObj[JSON_ID] = m_id;
  connectionJsonObj[JSON_NAME] = m_name;

  if (m_endPort) {
    connectionJsonObj[JSON_START_NODE_NAME] = m_startPort->parentNode()->name();
    connectionJsonObj[JSON_START_PORT_NUMBER] = QString::number(m_startPort->number());
    connectionJsonObj[JSON_END_NODE_NAME] = m_endPort->parentNode()->name();
    connectionJsonObj[JSON_END_PORT_NUMBER] = QString::number(m_endPort->number());
  } else if (m_endConnector) {
    connectionJsonObj[JSON_START_NODE_NAME] = m_startPort->parentNode()->name();
    connectionJsonObj[JSON_START_PORT_NUMBER] = QString::number(m_startPort->number());
    connectionJsonObj[JSON_CONNECTOR_POS_X] = QString::number(m_endConnector->scenePos().x());
    connectionJsonObj[JSON_CONNECTOR_POS_Y] = QString::number(m_endConnector->scenePos().y());
    connectionJsonObj[JSON_DST_CONNECTION_NAME] = m_endConnector->dstConnection()->name();
  }
  return connectionJsonObj;
}

void Connection::setEndConnector(Connector* endConnector) {
  m_endConnector = endConnector;
  m_endPos = endConnector->centerScenePos();
  redraw();
}

Connector* Connection::endConnector() const {
  return m_endConnector;
}

void Connection::removeEndConnector() {
  m_endConnector = nullptr;
}
