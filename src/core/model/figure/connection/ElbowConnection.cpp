#include "ElbowConnection.h"
#include "AbstractNode.h"
#include "Connector.h"
#include "Port.h"
#include "ProjectKeyDefine.h"
#include "SystemConfig.h"
#include <QPen>
#include <QUuid>

const static QString CONNECTION_ELBOW = "Elbow";

ElbowConnection::ElbowConnection(QGraphicsItem* parent) : AbstractConnection(parent) {
  m_connectionType = CONNECTION_ELBOW;
  m_pixmapFilePath = "../resource/elbowconnection.png";
}

ElbowConnection::~ElbowConnection() {
}

ElbowConnection* ElbowConnection::create(const QString& id) {
  ElbowConnection* connection = new ElbowConnection();
  connection->m_id = id;
  return connection;
}

// todo node dependency want to remove
// node will change to port.
QJsonObject ElbowConnection::toJsonObj() {
  QJsonObject connectionJsonObj;
  connectionJsonObj[JSON_ID] = m_id;
  connectionJsonObj[JSON_NAME] = m_name;
  connectionJsonObj[JSON_CONNECTION_TYPE] = m_connectionType;

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

QList<QPointF> ElbowConnection::createVertexes() {
  QList<QPointF> vertexes;

  if (hasEndConnector()) {
    AbstractConnection* targetConnection = m_endConnector->dstConnection();
    if (targetConnection && (Horizon == targetConnection->direction(m_endPos))) {
      vertexes << QPointF(m_endPos.x(), m_startPos.y());
      return vertexes;
    }
  }

  QPointF elbowPos = (m_startPos + m_endPos) * 0.5;
  vertexes << QPointF(elbowPos.x(), m_startPos.y()) << QPointF(elbowPos.x(), m_endPos.y());
  return vertexes;
}
