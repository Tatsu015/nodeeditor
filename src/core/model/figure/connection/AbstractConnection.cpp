#include "AbstractConnection.h"
#include "Connector.h"
#include "EdgeHandle.h"
#include "Port.h"
#include "SystemConfig.h"
#include "VertexHandle.h"
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QUuid>

const uint32_t AbstractConnection::PEN_SIZE = 3;

AbstractConnection::AbstractConnection(QGraphicsItem* parent)
    : QGraphicsPathItem(parent), m_id(QUuid::createUuid().toString()) {
  setPen(QPen(QColor(systemConfig(SystemConfig::connectionColor).toString()), PEN_SIZE));

  m_startEdgeHandle = new EdgeHandle(Start, this);
  m_endEdgeHandle = new EdgeHandle(End, this);
  m_startEdgeHandle->hide();
  m_endEdgeHandle->hide();
}

AbstractConnection::~AbstractConnection() {
}

void AbstractConnection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
  painter->setPen(pen());
  if (isSelected()) {
    m_startEdgeHandle->setPos(m_startPos);
    m_startEdgeHandle->show();
    m_endEdgeHandle->setPos(m_endPos);
    m_endEdgeHandle->show();
    foreach (VertexHandle* vertexHandle, m_vertexHandles) { vertexHandle->show(); }
  } else if (m_editingVertex) {
    m_startEdgeHandle->setPos(m_startPos);
    m_startEdgeHandle->show();
    m_endEdgeHandle->setPos(m_endPos);
    m_endEdgeHandle->show();
    foreach (VertexHandle* vertexHandle, m_vertexHandles) { vertexHandle->show(); }
  } else {
    m_startEdgeHandle->hide();
    m_endEdgeHandle->hide();
    foreach (VertexHandle* vertexHandle, m_vertexHandles) { vertexHandle->hide(); }
  }

  QStyleOptionGraphicsItem newOption(*option);
  newOption.state &= ~QStyle::State_Selected;
  QGraphicsPathItem::paint(painter, &newOption, widget);
}

QPainterPath AbstractConnection::shape() const {
  QPainterPathStroker pathStroker;
  return pathStroker.createStroke(path());
}

AbstractConnection* AbstractConnection::create() {
  return create(QUuid::createUuid().toString());
}

void AbstractConnection::created() {
  setFlag(ItemIsSelectable);
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

bool AbstractConnection::hasStartPort() const {
  if (m_startPort) {
    return true;
  }
  return false;
}

void AbstractConnection::setEndPort(Port* endPort) {
  m_endPort = endPort;
  m_endPos = endPort->endOfPortPos();
  redraw();
}

bool AbstractConnection::hasEndPort() const {
  if (m_endPort) {
    return true;
  }
  return false;
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

Port* AbstractConnection::inputPort() const {
  if (m_startPort) {
    if (Input == m_startPort->io()) {
      return m_startPort;
    }
  }
  if (m_endPort) {
    if (Input == m_endPort->io()) {
      return m_endPort;
    }
  }
  return nullptr;
}

bool AbstractConnection::hasInputPort() const {
  if (inputPort()) {
    return true;
  }
  return false;
}

Port* AbstractConnection::outputPort() const {
  if (m_startPort) {
    if (Output == m_startPort->io()) {
      return m_startPort;
    }
  }
  if (m_endPort) {
    if (Output == m_endPort->io()) {
      return m_endPort;
    }
  }
  return nullptr;
}

bool AbstractConnection::hasOutputPort() const {
  if (outputPort()) {
    return true;
  }
  return false;
}

int32_t AbstractConnection::areaIndex(QPointF pos, QSizeF searchSize) const {
  QVector<QPointF> elements = points();
  QRectF searchRect(pos, searchSize);
  searchRect.moveTo(-0.5 * searchSize.width(), 0.5 * searchSize.height());

  for (int32_t i = 0; i < elements.count() - 1; ++i) {
    QPainterPath searchArea;
    // +1 is mergin for easy to search target.
    QPointF ofs(searchSize.width() + 1, searchSize.height() + 1);
    searchArea.moveTo(elements[i] - ofs);
    searchArea.lineTo(elements[i] + ofs);
    searchArea.lineTo(elements[i + 1] + ofs);
    searchArea.lineTo(elements[i + 1] - ofs);
    searchArea.closeSubpath();

    if (searchArea.contains(pos)) {
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

Edge AbstractConnection::whichEdge(Port* port) {
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
  VertexHandle* vertexHandle = new VertexHandle(this);
  vertexHandle->setPos(vertex);
  m_vertexHandles << vertexHandle;
}

void AbstractConnection::addVertexes(QList<QPointF> vertexes) {
  foreach (QPointF vertex, vertexes) { addVertex(vertex); }
}

void AbstractConnection::insertVertex(VertexHandle* vertex, int32_t pos) {
  vertex->setParentItem(this);
  m_vertexHandles.insert(pos, vertex);
}

QList<QPointF> AbstractConnection::vertexes() const {
  QList<QPointF> vertexes;
  foreach (VertexHandle* vertexHandle, m_vertexHandles) { vertexes << vertexHandle->scenePos(); }
  return vertexes;
}

void AbstractConnection::removeVertex(VertexHandle* vertex) {
  m_vertexHandles.removeOne(vertex);
  redraw();
}

void AbstractConnection::startEditVertex() {
  m_editingVertex = true;
}

void AbstractConnection::endEditVertex() {
  m_editingVertex = false;
}

QList<AbstractConnection*> AbstractConnection::connectedConnections() {
  return connectedConnections(nullptr);
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

QList<AbstractConnection*> AbstractConnection::connectedConnections(const Connector* excludeConnector) {
  QList<AbstractConnection*> connections;
  connections << this;
  if (m_startConnector && (m_startConnector != excludeConnector)) {
    connections << m_startConnector->anotherConnection(this)->connectedConnections(m_startConnector);
  }
  if (m_endConnector && (m_endConnector != excludeConnector)) {
    connections << m_endConnector->anotherConnection(this)->connectedConnections(m_endConnector);
  }
  foreach (Connector* connector, m_branchConnectors) {
    if (connector != excludeConnector) {
      connections << connector->anotherConnection(this)->connectedConnections(connector);
    }
  }
  return connections;
}
