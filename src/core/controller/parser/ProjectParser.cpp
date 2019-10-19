#include "ProjectParser.h"
#include "AbstractNode.h"
#include "Connection.h"
#include "ConnectionFactory.h"
#include "ConnectorFactory.h"
#include "Define.h"
#include "NodeFactory.h"
#include "Port.h"
#include "PortFactory.h"
#include "Project.h"
#include "Sheet.h"
#include "SheetFactory.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

ProjectParser::ProjectParser() {
}

ProjectParser::~ProjectParser() {
}

Project* ProjectParser::parse(const QByteArray& data) {
  QJsonDocument doc(QJsonDocument::fromJson(data));
  QJsonObject rootObj(doc.object());

  Project* project = new Project();
  foreach (QJsonValue sheetJsonValue, rootObj[JSON_SHEETS].toArray()) {
    Sheet* sheet = parseSheet(sheetJsonValue);
    project->addSheet(sheet);
  }
  //  project->fromJson(rootObj);
  //  project->changeActiveSheet(0);

  return project;
}

Sheet* ProjectParser::parseSheet(QJsonValue sheetJsonVal) {
  Sheet* sheet = SheetFactory::getInstance()->createSheet(sheetJsonVal[JSON_ID].toString());
  sheet->setName(sheetJsonVal[JSON_NAME].toString());

  foreach (QJsonValue nodeJsonVal, sheetJsonVal[JSON_NODES].toArray()) {
    AbstractNode* node = parseNode(nodeJsonVal);
    sheet->addNode(node);
  }
  foreach (QJsonValue connectionJsonVal, sheetJsonVal[JSON_NODE_TO_NODE_CONNECTIONS].toArray()) {
    Connection* connection = parseNodeToNodeConnection(sheet, connectionJsonVal);
    sheet->addConnection(connection);
  }
  foreach (QJsonValue connectionJsonVal, sheetJsonVal[JSON_NODE_TO_CONNECTOR_CONNECTIONS].toArray()) {
    Connection* connection = parseNodeToConnectorConnection(sheet, connectionJsonVal);
    sheet->addConnection(connection);
  }
  return sheet;
}

AbstractNode* ProjectParser::parseNode(QJsonValue nodeJsonVal) {
  QString name = nodeJsonVal[JSON_NAME].toString();
  QString id = nodeJsonVal[JSON_ID].toString();
  QString nodeType = nodeJsonVal[JSON_NODETYPE].toString();
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

Connection* ProjectParser::parseNodeToNodeConnection(const Sheet* sheet, QJsonValue connectionJsonVal) {
  QString name = connectionJsonVal[JSON_NAME].toString();
  QString id = connectionJsonVal[JSON_ID].toString();
  QString startNodeName = connectionJsonVal[JSON_START_NODE_NAME].toString();
  uint32_t startPortNumber = connectionJsonVal[JSON_START_PORT_NUMBER].toString().toInt();
  QString endNodeName = connectionJsonVal[JSON_END_NODE_NAME].toString();
  uint32_t endPortNumber = connectionJsonVal[JSON_END_PORT_NUMBER].toString().toInt();

  Connection* connection = ConnectionFactory::getInstance()->createConnection(CONNECTION, name, id);
  AbstractNode* startNode = sheet->node(startNodeName);
  Port* startPort = startNode->port(startPortNumber);
  AbstractNode* endNode = sheet->node(endNodeName);
  Port* endPort = endNode->port(endPortNumber);

  connection->setName(name);
  connection->setStartPort(startPort);
  startPort->addConnection(connection);
  connection->setEndPort(endPort);
  endPort->addConnection(connection);

  return connection;
}

Connection* ProjectParser::parseNodeToConnectorConnection(const Sheet* sheet, QJsonValue connectionJsonVal) {
  QString name = connectionJsonVal[JSON_NAME].toString();
  QString id = connectionJsonVal[JSON_ID].toString();
  QString startNodeName = connectionJsonVal[JSON_START_NODE_NAME].toString();
  uint32_t startPortNumber = connectionJsonVal[JSON_START_PORT_NUMBER].toString().toInt();
  QString dstConnectionName = connectionJsonVal[JSON_DST_CONNECTION_NAME].toString();
  qreal connectorPosX = connectionJsonVal[JSON_CONNECTOR_POS_X].toString().toDouble();
  qreal connectorPosY = connectionJsonVal[JSON_CONNECTOR_POS_Y].toString().toDouble();

  Connection* connection = ConnectionFactory::getInstance()->createConnection(sheet, CONNECTION, name, id);
  Connector* endConnector = ConnectorFactory::getInstance()->createConnector(CONNECTOR, connection);
  endConnector->setPos(connectorPosX, connectorPosY);
  AbstractNode* startNode = sheet->node(startNodeName);
  Port* startPort = startNode->port(startPortNumber);
  Connection* dstConnection = sheet->connection(dstConnectionName);

  connection->setName(name);
  connection->setStartPort(startPort);
  startPort->addConnection(connection);

  connection->setEndConnector(endConnector);
  endConnector->setDstConnection(dstConnection);
  endConnector->setSrcConnection(connection);
  dstConnection->addBranchConnector(endConnector);

  return connection;
}
