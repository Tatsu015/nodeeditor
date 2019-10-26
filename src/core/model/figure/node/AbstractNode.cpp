#include "AbstractNode.h"
#include "Connection.h"
#include "Port.h"
#include "SystemConfig.h"
#include <QBrush>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QPainter>
#include <QPen>
#include <QUuid>

AbstractNode::AbstractNode(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
  setFlag(ItemIsSelectable);
  setFlag(ItemIsMovable);
  setFlag(ItemSendsGeometryChanges);

  setAcceptHoverEvents(true);

  const static QBrush BLUSH = QBrush(QColor(systemConfig(SystemConfig::nodeFillColor).toString()));
  const static QPen PEN = QPen(QColor(systemConfig(SystemConfig::nodeLineColor).toString()), PEN_SIZE);
  setBrush(BLUSH);
  setPen(PEN);
}

AbstractNode::~AbstractNode() {
  qDeleteAll(m_ports);
}

void AbstractNode::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
  QGraphicsPathItem::hoverEnterEvent(event);
}

void AbstractNode::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {
  QGraphicsPathItem::hoverMoveEvent(event);
}

void AbstractNode::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
  QGraphicsPathItem::hoverLeaveEvent(event);
}

QVariant AbstractNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value) {
  if (ItemPositionChange == change) {
    foreach (Port* port, m_ports) {
      foreach (Connection* connection, port->connections()) { connection->redraw(); }
    }
  }
  return QGraphicsPathItem::itemChange(change, value);
}

AbstractNode* AbstractNode::create() {
  return create(QUuid::createUuid().toString());
}

QString AbstractNode::name() const {
  return m_name;
}

void AbstractNode::setName(const QString& name) {
  m_name = name;
}

qreal AbstractNode::top() const {
  return sceneBoundingRect().top();
}

qreal AbstractNode::bottom() const {
  return sceneBoundingRect().bottom();
}

qreal AbstractNode::right() const {
  return sceneBoundingRect().right();
}

qreal AbstractNode::left() const {
  return sceneBoundingRect().left();
}

QPointF AbstractNode::centerOffset() const {
  QPointF offset(boundingRect().center());
  return offset;
}

void AbstractNode::setup() {
  setupNameText();
  doSetup();
}

void AbstractNode::setupNameText() {
  m_nameText = new QGraphicsSimpleTextItem(m_name, this);
  m_nameText->setPos(0, -20);
  m_nameText->setPen(QPen(Qt::white));
  m_nameText->setBrush(QBrush(Qt::white));
}

void AbstractNode::doSetup() {
}

QList<Port*> AbstractNode::ports() const {
  return m_ports;
}

int32_t AbstractNode::portCount() const {
  return ports().count();
}

void AbstractNode::addPort(Port* port) {
  m_ports << port;
}

void AbstractNode::addInputPort(Port* inputPort) {
  if (m_maxInputPortCount < inputPortCount()) {
    qDebug() << "Too many input port exist!";
    return;
  }
  m_ports << inputPort;
  adjustInputPortPos();
}

void AbstractNode::addOutputPort(Port* outputPort) {
  if (m_maxOutputPortCount < outputPortCount()) {
    qDebug() << "Too many output port exist!";
    return;
  }
  m_ports << outputPort;
  adjustOutputPortPos();
}

bool AbstractNode::canAddInputPort() const {
  if (m_maxInputPortCount <= inputPortCount()) {
    return false;
  }
  return true;
}

bool AbstractNode::canAddOutputPort() const {
  if (m_maxOutputPortCount <= outputPortCount()) {
    return false;
  }
  return true;
}

void AbstractNode::removePort(Port* port) {
  foreach (Port* p, m_ports) {
    if (p == port) {
      m_ports.removeOne(p);
      p->setParentItem(nullptr);
    }
  }
  if (Input == port->io()) {
    adjustInputPortPos();
  } else {
    adjustOutputPortPos();
  }
}

bool AbstractNode::canRemoveInputPort() const {
  if (m_minInputPortCount >= inputPortCount()) {
    return false;
  }
  return true;
}

bool AbstractNode::canRemoveOutputPort() const {
  if (m_minOutputPortCount >= outputPortCount()) {
    return false;
  }
  return true;
}

Port* AbstractNode::port(const uint64_t number) {
  foreach (Port* port, m_ports) {
    if (number == port->number()) {
      return port;
    }
  }
  return nullptr;
}

Port* AbstractNode::nearestPort(QPointF scenePos) {
  qreal minLengthToPort = (m_ports.at(0)->pos() - scenePos).manhattanLength();
  Port* nearestPort = m_ports.at(0);
  foreach (Port* port, m_ports) {
    QPointF diff = port->pos() - scenePos;
    qreal length = diff.manhattanLength();
    if (minLengthToPort > length) {
      minLengthToPort = length;
      nearestPort = port;
    }
  }
  return nearestPort;
}
QList<Port*> AbstractNode::inputPorts() const {
  QList<Port*> ports;
  foreach (Port* port, m_ports) {
    if (Input == port->io()) {
      ports << port;
    }
  }
  return ports;
}

QList<Port*> AbstractNode::outputPorts() const {
  QList<Port*> ports;
  foreach (Port* port, m_ports) {
    if (Output == port->io()) {
      ports << port;
    }
  }
  return ports;
}

int32_t AbstractNode::inputPortCount() const {
  return inputPorts().count();
}

int32_t AbstractNode::outputPortCount() const {
  return outputPorts().count();
}

QList<AbstractNode*> AbstractNode::adjastOutNodes() {
  QList<AbstractNode*> nodes;
  foreach (Port* port, m_ports) {
    foreach (Connection* connection, port->connections()) {
      AbstractNode* outNode = dynamic_cast<AbstractNode*>(connection->endPort()->parentItem());
      if (outNode != this) {
        nodes << outNode;
      }
    }
  }
  return nodes;
}

QList<AbstractNode*> AbstractNode::adjastInNodes() {
  QList<AbstractNode*> nodes;
  foreach (Port* port, m_ports) {
    foreach (Connection* connection, port->connections()) {
      AbstractNode* inNode = dynamic_cast<AbstractNode*>(connection->startPort()->parentItem());
      if (inNode != this) {
        nodes << inNode;
      }
    }
  }
  return nodes;
}

QList<AbstractNode*> AbstractNode::adjastNodes() {
  QList<AbstractNode*> nodes;
  foreach (Port* port, m_ports) {
    foreach (Connection* connection, port->connections()) {
      AbstractNode* inNode = dynamic_cast<AbstractNode*>(connection->startPort()->parentItem());
      if (inNode != this) {
        // when exist loop, this check need
        if (!nodes.contains(inNode)) {
          nodes << inNode;
        }
      }
      AbstractNode* outNode = dynamic_cast<AbstractNode*>(connection->endPort()->parentItem());
      if (outNode != this) {
        // when exist loop, this check need
        if (!nodes.contains(outNode)) {
          nodes << outNode;
        }
      }
    }
  }

  return nodes;
}

EPosition AbstractNode::portPosition(Port* port) {
  QPointF center = sceneBoundingRect().center();
  QPointF portCenter = port->sceneBoundingRect().center();

  QPointF centerDiffVector = portCenter - center;
  QPointF originDirVector = QPointF(1, 0);

  QLineF diffLine(QPointF(0, 0), centerDiffVector);
  QLineF originLine(QPointF(0, 0), originDirVector);

  qreal angle = diffLine.angleTo(originLine);

  if ((45 <= angle) && (angle < 135)) {
    return Bottom;
  } else if ((135 <= angle) && (angle < 225)) {
    return Left;
  } else if ((225 <= angle) && (angle < 315)) {
    return Top;
  } else {
    return Right;
  }
  return Top;
}

QString AbstractNode::nodeType() const {
  return m_nodeType;
}

void AbstractNode::setNodeType(const QString& nodeType) {
  m_nodeType = nodeType;
}

void AbstractNode::redraw() {
  foreach (Port* port, m_ports) { port->redraw(); }
}

IO AbstractNode::io() const {
  return m_io;
}

void AbstractNode::changeColor(const QColor color) {
  setBrush(QBrush(color));
}

void AbstractNode::resetColor() {
  setBrush(QBrush(QColor(systemConfig(SystemConfig::nodeFillColor).toString())));
}

void AbstractNode::setNameTextVisible(const bool visible) {
  if (visible) {
    m_nameText->show();
  } else {
    m_nameText->hide();
  }
}

QString AbstractNode::id() const {
  return m_id;
}

QJsonObject AbstractNode::toJsonObject() {
  QJsonObject jsonObj;
  jsonObj[JSON_ID] = m_id;
  jsonObj[JSON_NAME] = m_name;
  jsonObj[JSON_NODETYPE] = m_nodeType;
  jsonObj[JSON_X] = pos().x();
  jsonObj[JSON_Y] = pos().y();

  QJsonArray portJsonArray;
  foreach (Port* port, m_ports) { portJsonArray.append(port->toJsonObj()); }

  jsonObj[JSON_PORTS] = portJsonArray;

  return jsonObj;
}

void AbstractNode::adjustInputPortPos() {
  int32_t portCount = inputPortCount();

  if (portCount < 1) {
    return;
  }

  QList<Port*> ports = inputPorts();
  if (portCount < 2) {
    Port* port = ports.first();
    port->setPos(-port->boundingRect().width() + PORT_POS_X_OFS,
                 boundingRect().center().y() - port->boundingRect().height() * 0.5);
    return;
  }

  qreal span = (boundingRect().height() - PORT_POS_Y_OFS * 2 - ports.first()->boundingRect().height() * portCount) /
               (portCount - 1);

  qreal y = PORT_POS_Y_OFS;
  foreach (Port* port, ports) {
    port->setPos(-port->boundingRect().width() + PORT_POS_X_OFS, y);
    y += (port->boundingRect().height() + span);
  }
}

void AbstractNode::adjustOutputPortPos() {
  int32_t portCount = outputPortCount();

  if (portCount < 1) {
    return;
  }

  QList<Port*> ports = outputPorts();
  if (portCount < 2) {
    Port* port = ports.first();
    port->setPos(boundingRect().width() - PORT_POS_X_OFS,
                 boundingRect().center().y() - port->boundingRect().height() * 0.5);
    return;
  }

  qreal span = (boundingRect().height() - PORT_POS_Y_OFS * 2 - ports.first()->boundingRect().height() * portCount) /
               (portCount - 1);

  qreal y = PORT_POS_Y_OFS;
  foreach (Port* port, ports) {
    port->setPos(boundingRect().width() - PORT_POS_X_OFS, y);
    y += (port->boundingRect().height() + span);
  }
}
