#include "AbstractNode.h"
#include "Connection.h"
#include "Port.h"
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QUuid>

const QColor AbstractNode::FILL_COLOR = QColor("#666666");
const QColor AbstractNode::LINE_COLOR = QColor("#AAAAAA");

AbstractNode::AbstractNode(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
  setFlag(ItemIsSelectable);
  setFlag(ItemIsMovable);
  setFlag(ItemSendsGeometryChanges);

  setAcceptHoverEvents(true);

  const static QBrush BLUSH = QBrush(FILL_COLOR);
  const static QPen PEN = QPen(LINE_COLOR, PEN_SIZE);
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

void AbstractNode::setupNameText() {
  m_nameText = new QGraphicsSimpleTextItem(m_name, this);
  m_nameText->setPos(0, -20);
  m_nameText->setPen(QPen(Qt::white));
  m_nameText->setBrush(QBrush(Qt::white));
}

QList<Port*> AbstractNode::ports() const {
  return m_ports;
}

void AbstractNode::addPort(Port* port) {
  m_ports << port;
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
  setBrush(QBrush(FILL_COLOR));
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
