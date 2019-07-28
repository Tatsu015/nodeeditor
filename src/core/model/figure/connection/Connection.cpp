#include "Connection.h"
#include "Connector.h"
#include "Define.h"
#include "Port.h"
#include <QPen>

const QColor Connection::LINE_COLOR = QColor("#AAAAAA");
const uint32_t Connection::PEN_SIZE = 3;

Connection::Connection(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
  m_connectionType = CONNECTION;
  setPen(QPen(LINE_COLOR, PEN_SIZE));
}

Connection::~Connection() {
}

Connection* Connection::create() {
  return new Connection();
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
  m_startPos = startPort->centerScenePos();
  redraw();
}

void Connection::setEndPort(Port* endPort) {
  m_endPort = endPort;
  m_endPos = endPort->centerScenePos();
  redraw();
}

void Connection::redraw() {
  // m_startPos and m_endPos need to change. Because port and connector position updated by QGraphicsItem::ItemMove, But
  // m_startPos and m_endPos cannot update!
  if (m_startPort) {
    m_startPos = m_startPort->centerScenePos();
  }
  if (m_endPort) {
    m_endPos = m_endPort->centerScenePos();
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

QRectF Connection::areaR(QPointF pos, QSizeF searchSize) const {
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
      return r;
    }
  }
  return QRectF();
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

void Connection::addBranchConnector(Connector* connector) {
  connector->setParentItem(this);
  m_branchConnectors << connector;
}

void Connection::removeBranchConnector(Connector* connector) {
  m_branchConnectors.removeOne(connector);
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

void Connection::setEndConnector(Connector* endConnector) {
  m_endConnector = endConnector;
  m_endPos = endConnector->centerScenePos();
  redraw();
}

void Connection::removeEndConnector() {
  m_endConnector = nullptr;
}
