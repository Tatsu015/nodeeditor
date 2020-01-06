#include "AbstractConnection.h"
#include "Connector.h"
#include "Define.h"
#include "Port.h"
#include "SystemConfig.h"
#include <QPen>
#include <QUuid>

const uint32_t AbstractConnection::PEN_SIZE = 3;

AbstractConnection::AbstractConnection(QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_id(QUuid::createUuid().toString()) {
  setPen(QPen(QColor(systemConfig(SystemConfig::connectionColor).toString()), PEN_SIZE));
}

AbstractConnection::~AbstractConnection() {
}

AbstractConnection* AbstractConnection::create() {
  return create(QUuid::createUuid().toString());
}

QPixmap AbstractConnection::pixmap() const {
  return QPixmap(m_pixmapFilePath);
}

QPointF AbstractConnection::startPos() const {
  return m_startPos;
}

void AbstractConnection::setStartPos(const QPointF& startPos) {
  m_startPos = startPos;
  redraw();
}

QPointF AbstractConnection::endPos() const {
  return m_endPos;
}

void AbstractConnection::setEndPos(const QPointF& endPos) {
  m_endPos = endPos;
  redraw();
}

void AbstractConnection::setStartPort(Port* startPort) {
  m_startPort = startPort;
  m_startPos = startPort->endOfPortPos();
  redraw();
}

void AbstractConnection::setEndPort(Port* endPort) {
  m_endPort = endPort;
  m_endPos = endPort->endOfPortPos();
  redraw();
}

void AbstractConnection::redraw(Port* startPort, Port* endPort) {
  m_startPort = startPort;
  m_endPort = endPort;
  redraw();
}

void AbstractConnection::redraw(Port* startPort, QPointF endScenePos) {
  m_startPort = startPort;
  m_endPos = endScenePos;
  redraw();
}

Port* AbstractConnection::startPort() const {
  return m_startPort;
}

Port* AbstractConnection::endPort() const {
  return m_endPort;
}

void AbstractConnection::removeStartPort() {
  m_startPort = nullptr;
}

void AbstractConnection::removeEndPort() {
  m_endPort = nullptr;
}

Port* AbstractConnection::oppositeSidePort(Port* port) {
  if (port == m_startPort) {
    return m_endPort;
  } else {
    return m_startPort;
  }
}

int32_t AbstractConnection::areaIndex(QPointF pos, QSizeF searchSize) const {
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

QPointF AbstractConnection::closeCenter(QPointF pos, QSizeF searchSize) {
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

AbstractConnection::Direction AbstractConnection::direction(QPointF pos, QSizeF searchSize) const {
  QVector<QPointF> elements = points();
  for (int i = 0; i < elements.count() - 1; ++i) {
    QRectF r(elements[i], elements[i + 1]);
    QRectF dmg;
    AbstractConnection::Direction direction = Vertical;
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

AbstractConnection::Edge AbstractConnection::whichEdge(Port* port) {
  if (m_startPort == port) {
    return Start;
  } else if (m_endPort == port) {
    return End;
  } else {
    return None;
  }
}

Connector* AbstractConnection::startConnector() const {
  return m_startConnector;
}

bool AbstractConnection::hasStartConnector() const {
  if (m_startConnector) {
    return true;
  }
  return false;
}

Connector* AbstractConnection::endConnector() const {
  return m_endConnector;
}

void AbstractConnection::setEndConnector(Connector* endConnector) {
  m_endConnector = endConnector;
  m_endPos = endConnector->centerScenePos();
  redraw();
}

void AbstractConnection::removeEndConnector() {
  m_endConnector = nullptr;
}

bool AbstractConnection::hasEndConnector() const {
  if (m_endConnector) {
    return true;
  }
  return false;
}

void AbstractConnection::addBranchConnector(Connector* connector) {
  connector->setParentItem(this);
  m_branchConnectors << connector;
}

void AbstractConnection::removeBranchConnector(Connector* connector) {
  m_branchConnectors.removeOne(connector);
}

QList<Connector*> AbstractConnection::branchConnectors() const {
  return m_branchConnectors;
}

void AbstractConnection::addVertex(QPointF vertex) {
  m_vertexes << vertex;
}

void AbstractConnection::addVertexes(QList<QPointF> vertex) {
  m_vertexes = vertex;
}

QList<QPointF> AbstractConnection::vertexes() const {
  return m_vertexes;
}

QString AbstractConnection::name() const {
  return m_name;
}

void AbstractConnection::setName(const QString& name) {
  m_name = name;
}

QString AbstractConnection::connectionType() const {
  return m_connectionType;
}

QString AbstractConnection::id() const {
  return m_id;
}

void AbstractConnection::changeConnectionStyle(const AbstractConnection::ConnectionStyle style) {
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

QVector<QPointF> AbstractConnection::points() const {
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
