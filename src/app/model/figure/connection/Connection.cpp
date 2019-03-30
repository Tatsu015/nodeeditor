#include "Connection.h"
#include <QPen>
#include "Connector.h"
#include "Define.h"
#include "Port.h"

const QColor Connection::LINE_COLOR = QColor("#AAAAAA");
const uint32_t Connection::PEN_SIZE = 3;

Connection::Connection(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
  m_connectionType = CONNECTION;
  setPen(QPen(LINE_COLOR, PEN_SIZE));
}

Connection::~Connection() {}

Connection* Connection::create() { return new Connection(); }

void Connection::setStartPos(const QPointF& startPos) {
  m_startPos = startPos;
  redraw();
}

void Connection::setEndPos(const QPointF& endPos) {
  m_endPos = endPos;
  redraw();
}

void Connection::setStartPort(Port* startPort) {
  m_startPort = startPort;
  redraw();
}

void Connection::setEndPort(Port* endPort) {
  m_endPort = endPort;
  redraw();
}

void Connection::redraw() {
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

void Connection::setStartConnector(Connector* startConnector)
{
    m_startConnector = startConnector;
}

void Connection::removeStartConnector()
{
    m_startConnector = nullptr;
}

void Connection::addBranchConnector(Connector* connector, QPointF scenePos) {
  connector->setParentItem(this);
  connector->setPos(scenePos + connector->centerOffset());
  m_branchConnectors << connector;
}

void Connection::removeBranchConnector(Connector* connector)
{
  m_branchConnectors.removeOne(connector);
}

QString Connection::name() const { return m_name; }

void Connection::setName(const QString& name) { m_name = name; }

QString Connection::connectionType() const { return m_connectionType; }

void Connection::setEndConnector(Connector* endConnector)
{
  m_endConnector = endConnector;
}

void Connection::removeEndConnector()
{
  m_endConnector = nullptr;
}
