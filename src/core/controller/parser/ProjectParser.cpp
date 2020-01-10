#include "ProjectParser.h"
#include "AbstractConnection.h"
#include "AbstractNode.h"
#include "ConnectionFactory.h"
#include "ConnectorFactory.h"
#include "JsonUtil.h"
#include "NodeFactory.h"
#include "Port.h"
#include "PortFactory.h"
#include "Project.h"
#include "ProjectKeyDefine.h" "
#include "Sheet.h"
#include "SheetFactory.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

ProjectParser::ProjectParser() {
}

ProjectParser::~ProjectParser() {
}

Project* ProjectParser::parse(const QByteArray& data, Project* lastProject) {
  QJsonDocument doc(QJsonDocument::fromJson(data));
  QJsonObject rootObj(doc.object());

  Project* project = new Project();
  project->takeOver(lastProject);
  foreach (QJsonValue sheetJsonValue, rootObj[JSON_SHEETS].toArray()) {
    Sheet* sheet = parseSheet(sheetJsonValue);
    project->addSheet(sheet);
  }

  return project;
}

Sheet* ProjectParser::parseSheet(QJsonValue sheetJsonVal) {
  QString id = sheetJsonVal[JSON_ID].toString();
  QString name = sheetJsonVal[JSON_NAME].toString();
  Sheet* sheet = SheetFactory::getInstance()->createSheet(name, id);

  foreach (QJsonValue nodeJsonVal, sheetJsonVal[JSON_NODES].toArray()) {
    AbstractNode* node = parseNode(nodeJsonVal);
    sheet->addNode(node);
  }
  foreach (QJsonValue connectionJsonVal, sheetJsonVal[JSON_NODE_TO_NODE_CONNECTIONS].toArray()) {
    AbstractConnection* connection = parseNodeToNodeConnection(sheet, connectionJsonVal);
    sheet->addConnection(connection);
  }
  foreach (QJsonValue connectionJsonVal, sheetJsonVal[JSON_NODE_TO_CONNECTOR_CONNECTIONS].toArray()) {
    AbstractConnection* connection = parseNodeToConnectorConnection(sheet, connectionJsonVal);
    sheet->addConnection(connection);
  }
  return sheet;
}

AbstractNode* ProjectParser::parseNode(QJsonValue nodeJsonVal) {
  QString name = nodeJsonVal[JSON_NAME].toString();
  QString id = nodeJsonVal[JSON_ID].toString();
  QString nodeType = nodeJsonVal[JSON_NODE_TYPE].toString();
  qreal x = nodeJsonVal[JSON_X].toDouble();
  qreal y = nodeJsonVal[JSON_Y].toDouble();

  AbstractNode* node = NodeFactory::getInstance()->createNode(nodeType, name, id);
  node->setName(name);
  node->setPos(x, y);

  foreach (QJsonValue portJsonValue, nodeJsonVal[JSON_PORTS].toArray()) {
    uint32_t portNum = static_cast<uint32_t>(portJsonValue[JSON_PORT_NUMBER].toInt());
    Port* port = node->port(portNum);
    bool isInverted = portJsonValue[JSON_PORT_INVERTED].toBool();
    if (port) {
      port->invert(isInverted);
    } else {
      IO io = static_cast<IO>(portJsonValue[JSON_PORT_IO].toInt());
      port = PortFactory::getInstance()->createPort("port", io, node, isInverted);
      if (Input == io) {
        node->addInputPort(port);
      } else {
        node->addOutputPort(port);
      }
    }
  }
  return node;
}

AbstractConnection* ProjectParser::parseNodeToNodeConnection(const Sheet* sheet, QJsonValue connectionJsonVal) {
  QString name = connectionJsonVal[JSON_NAME].toString();
  QString id = connectionJsonVal[JSON_ID].toString();
  QString connectionType = connectionJsonVal[JSON_CONNECTION_TYPE].toString();
  QString startNodeName = connectionJsonVal[JSON_CONNECTION_START_NODE_NAME].toString();
  uint32_t startPortNumber = connectionJsonVal[JSON_CONNECTION_START_PORT_NUMBER].toString().toInt();
  QString endNodeName = connectionJsonVal[JSON_CONNECTION_END_NODE_NAME].toString();
  uint32_t endPortNumber = connectionJsonVal[JSON_CONNECTION_END_PORT_NUMBER].toString().toInt();
  QList<QPointF> vertexes = jsonToPointFs(connectionJsonVal[JSON_CONNECTION_VERTEX_POSES].toArray());

  AbstractConnection* connection = ConnectionFactory::getInstance()->createConnection(connectionType, name, id);
  AbstractNode* startNode = sheet->node(startNodeName);
  Port* startPort = startNode->port(startPortNumber);
  AbstractNode* endNode = sheet->node(endNodeName);
  Port* endPort = endNode->port(endPortNumber);

  connection->setName(name);
  connection->setStartPort(startPort);
  startPort->addConnection(connection);
  connection->setEndPort(endPort);
  connection->addVertexes(vertexes);
  endPort->addConnection(connection);

  return connection;
}

AbstractConnection* ProjectParser::parseNodeToConnectorConnection(const Sheet* sheet, QJsonValue connectionJsonVal) {
  QString name = connectionJsonVal[JSON_NAME].toString();
  QString id = connectionJsonVal[JSON_ID].toString();
  QString connectionType = connectionJsonVal[JSON_CONNECTION_TYPE].toString();
  QString startNodeName = connectionJsonVal[JSON_CONNECTION_START_NODE_NAME].toString();
  uint32_t startPortNumber = connectionJsonVal[JSON_CONNECTION_START_PORT_NUMBER].toString().toInt();
  QString dstConnectionName = connectionJsonVal[JSON_CONNECTOR_DST_CONNECTION_NAME].toString();
  qreal posXRate = connectionJsonVal[JSON_CONNECTOR_POS_X_RATE].toString().toDouble();
  qreal posYRate = connectionJsonVal[JSON_CONNECTOR_POS_Y_RATE].toString().toDouble();

  AbstractConnection* connection = ConnectionFactory::getInstance()->createConnection(sheet, connectionType, name, id);
  AbstractNode* startNode = sheet->node(startNodeName);
  Port* startPort = startNode->port(startPortNumber);
  AbstractConnection* dstConnection = sheet->connection(dstConnectionName);
  Connector* endConnector = ConnectorFactory::getInstance()->createConnector(CONNECTOR, dstConnection);

  endConnector->setXPosRate(posXRate);
  endConnector->setYPosRate(posYRate);

  connection->setName(name);
  connection->setStartPort(startPort);
  startPort->addConnection(connection);

  connection->setEndConnector(endConnector);
  endConnector->setDstConnection(dstConnection);
  endConnector->setSrcConnection(connection);
  dstConnection->addBranchConnector(endConnector);

  return connection;
}
