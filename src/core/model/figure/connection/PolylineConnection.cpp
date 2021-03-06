#include "PolylineConnection.h"
#include "Connector.h"
#include "JsonUtil.h"
#include "Port.h"
#include "ProjectKeyDefine.h"
#include "SystemConfig.h"
#include <QPen>
#include <QUuid>

PolylineConnection::PolylineConnection(QGraphicsItem* parent) : AbstractConnection(parent) {
  m_connectionType = CONNECTION_POLYLINE;
  m_pixmapFilePath = "../resource/polylineconnection.png";
}

PolylineConnection::~PolylineConnection() {
}

PolylineConnection* PolylineConnection::create(const QString& id) {
  PolylineConnection* polylineConnection = new PolylineConnection();
  polylineConnection->m_id = id;
  return polylineConnection;
}

// todo node dependency want to remove
// node will change to port.
#include "AbstractNode.h"
QJsonObject PolylineConnection::toJsonObj() {
  QJsonObject connectionJsonObj;
  connectionJsonObj[JSON_ID] = m_id;
  connectionJsonObj[JSON_NAME] = m_name;
  connectionJsonObj[JSON_CONNECTION_TYPE] = m_connectionType;
  connectionJsonObj[JSON_CONNECTION_VERTEX_POSES] = pointFsToJson(vertexes());

  if (m_endPort) {
    connectionJsonObj[JSON_CONNECTION_START_NODE_NAME] = m_startPort->parentNode()->name();
    connectionJsonObj[JSON_CONNECTION_START_PORT_NUMBER] = QString::number(m_startPort->number());
    connectionJsonObj[JSON_CONNECTION_END_NODE_NAME] = m_endPort->parentNode()->name();
    connectionJsonObj[JSON_CONNECTION_END_PORT_NUMBER] = QString::number(m_endPort->number());
  } else if (m_endConnector) {
    connectionJsonObj[JSON_CONNECTION_START_NODE_NAME] = m_startPort->parentNode()->name();
    connectionJsonObj[JSON_CONNECTION_START_PORT_NUMBER] = QString::number(m_startPort->number());
    connectionJsonObj[JSON_CONNECTOR_POS_X_RATE] = QString::number(m_endConnector->xPosRate());
    connectionJsonObj[JSON_CONNECTOR_POS_Y_RATE] = QString::number(m_endConnector->yPosRate());
    connectionJsonObj[JSON_CONNECTOR_DST_CONNECTION_NAME] = m_endConnector->dstConnection()->name();
  }
  return connectionJsonObj;
}

QList<QPointF> PolylineConnection::createVertexes() {
  return vertexes();
}
