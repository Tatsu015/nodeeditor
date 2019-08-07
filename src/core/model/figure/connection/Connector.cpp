#include "Connector.h"
#include "Connection.h"
#include <QBrush>
#include <QPen>

const static int CONNECTOR_RADIUS = 10;

Connector::Connector(QGraphicsItem* parent) : QGraphicsPathItem(parent) {
  setPen(QPen(Qt::gray, 1));
  setBrush(QBrush(Qt::gray));

  QPainterPath path;
  path.addEllipse(-CONNECTOR_RADIUS, -CONNECTOR_RADIUS, CONNECTOR_RADIUS, CONNECTOR_RADIUS);
  setPath(path);
}

Connector::~Connector() {
}

Connector* Connector::create(QGraphicsItem* parent) {
  return new Connector(parent);
}

QPointF Connector::centerScenePos() {
  return sceneBoundingRect().center();
}

QString Connector::connectorType() const {
  return "Connector";
}

Connection* Connector::dstConnection() const {
  return m_dstConnection;
}

void Connector::setDstConnection(Connection* fromConnection) {
  m_dstConnection = fromConnection;
}

Connection* Connector::srcConnection() const {
  return m_srcConnection;
}

void Connector::setSrcConnection(Connection* srcConnection) {
  m_srcConnection = srcConnection;
  setParentItem(srcConnection);
}

void Connector::removeSrcConnection() {
  m_srcConnection->removeBranchConnector(this);
  m_srcConnection = nullptr;
}

void Connector::removeDstConnection() {
  m_dstConnection->removeBranchConnector(this);
  m_dstConnection = nullptr;
}

QPointF Connector::centerOffset() const {
  QPointF offset(CONNECTOR_RADIUS * 0.5, CONNECTOR_RADIUS * 0.5);
  return offset;
}

QString Connector::name() const {
  return m_name;
}

void Connector::setName(const QString& name) {
  m_name = name;
}

qreal Connector::xPosRate() const {
  return m_xPosRate;
}

void Connector::setXPosRate(const qreal& xPosRate) {
  m_xPosRate = xPosRate;
}

qreal Connector::yPosRate() const {
  return m_yPosRate;
}

void Connector::setYPosRate(const qreal& yPosRate) {
  m_yPosRate = yPosRate;
}