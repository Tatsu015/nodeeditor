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

void Connector::setDstConnection(Connection* dstConnection) {
  m_dstConnection = dstConnection;
}

void Connector::setSrcConnection(Connection* srcConnection) {
  m_srcConnection = srcConnection;
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
