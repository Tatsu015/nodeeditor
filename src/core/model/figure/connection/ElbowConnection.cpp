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

void ElbowConnection::redraw() {
  // m_startPos and m_endPos need to change. Because port and connector position updated by QGraphicsItem::ItemMove, But
  // m_startPos and m_endPos cannot update!
  if (m_startPort) {
    m_startPos = m_startPort->endOfPortPos();
  }
  if (m_endPort) {
    m_endPos = m_endPort->endOfPortPos();
  }
  if (m_endConnector) {
    m_endPos = m_endConnector->centerScenePos();
  }

  QPointF elbowPos = (m_startPos + m_endPos) * 0.5;

  foreach (Connector* connector, m_branchConnectors) {
    QPointF pos = m_endPos - m_startPos;
    QPointF connectorPos(m_startPos.x() + pos.x() * connector->xPosRate(),
                         m_startPos.y() + pos.y() * connector->yPosRate());
    connectorPos += connector->centerOffset();
    connector->setPos(connectorPos);
    // redraw connector connected connection
    connector->srcConnection()->redraw();
  }

  QPainterPath path;
  QPointF elbow1(elbowPos.x(), m_startPos.y());
  QPointF elbow2(elbowPos.x(), m_endPos.y());
  path.moveTo(m_startPos);
  path.lineTo(elbow1);
  path.lineTo(elbow2);
  path.lineTo(m_endPos);
  setPath(path);
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
