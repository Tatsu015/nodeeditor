#include "Connection.h"
#include <QPen>
#include "Connector.h"
#include "Define.h"
#include "Port.h"

Connection::Connection(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
  m_connectionType = CONNECTION;
  setPen(QPen(Qt::gray, 2));
}

Connection::~Connection() {}

Connection* Connection::create() { return new Connection(); }

void Connection::setStartPos(const QPointF& startPos) {
  m_startPos = startPos;
  updatePath();
}

void Connection::setEndPos(const QPointF& endPos) {
  m_endPos = endPos;
  updatePath();
}

void Connection::setStartPort(Port* startPort) {
  m_startPort = startPort;
  updatePath();
}

void Connection::setEndPort(Port* endPort) {
  m_endPort = endPort;
  updatePath();
}

#include <QDebug>
void Connection::updatePath() {
  QPointF startPos = m_startPos;
  QPointF endPos = m_endPos;
  if (m_startPort) {
    startPos = m_startPort->centerScenePos();
  }
  if (m_endPort) {
    endPos = m_endPort->centerScenePos();
  }

  QPointF elbowPos = (startPos + endPos) * 0.5;

  QPainterPath path;
  QPointF elbow1(elbowPos.x(), startPos.y());
  QPointF elbow2(elbowPos.x(), endPos.y());
  path.moveTo(startPos);
  path.lineTo(elbow1);
  path.lineTo(elbow2);
  path.lineTo(endPos);
  path.lineTo(elbow2);
  path.lineTo(elbow1);
  path.closeSubpath();
  setPath(path);
}

void Connection::updatePath(Port* startPort, Port* endPort) {
  m_startPort = startPort;
  m_endPort = endPort;
  updatePath();
}

void Connection::updatePath(Port* startPort, QPointF endScenePos) {
  m_startPort = startPort;
  m_endPos = endScenePos;
  updatePath();
}

Port* Connection::startPort() const { return m_startPort; }

Port* Connection::endPort() const { return m_endPort; }

void Connection::removeStartPort() { m_startPort = nullptr; }

void Connection::removeEndPort() { m_endPort = nullptr; }

Port* Connection::oppositeSidePort(Port* port) {
  if (port == m_startPort) {
    return m_endPort;
  } else {
    return m_startPort;
  }
}

void Connection::addConnector(Connector* connector) {
  connector->setParentItem(this);
  m_connectors << connector;
}

QString Connection::name() const { return m_name; }

void Connection::setName(const QString& name) { m_name = name; }

QString Connection::connectionType() const { return m_connectionType; }
