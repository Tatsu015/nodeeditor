#include "Project.h"
#include "AbstractNode.h"
#include "Connection.h"
#include "ConnectionFactory.h"
#include "Connector.h"
#include "ConnectorFactory.h"
#include "Define.h"
#include "Editor.h"
#include "NodeFactory.h"
#include "Port.h"
#include "Scene.h"
#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

const static QString DEFAULT_FILE_NAME = "Undefined." + APP_EXTENSION;
const static QString JSON_NODE_NAME_VISIBLE = "nodeNameVisible";
const static QString JSON_NODES = "nodes";
const static QString JSON_PORTS = "ports";
const static QString JSON_CONNECTORS = "connectors";
const static QString JSON_NODE_TO_NODE_CONNECTIONS = "nodeToNodeConnections";
const static QString JSON_NODE_TO_CONNECTOR_CONNECTIONS = "nodeToConnectorConnections";
const static QString JSON_NAME = "name";
const static QString JSON_NODETYPE = "nodetype";
const static QString JSON_PORT_NUMBER = "portNumber";
const static QString JSON_PORT_INVERTED = "portInverted";
const static QString JSON_X = "x";
const static QString JSON_Y = "y";
const static QString JSON_START_NODE_NAME = "startNodeName";
const static QString JSON_START_PORT_NUMBER = "startPortNumber";
const static QString JSON_END_NODE_NAME = "endNodeName";
const static QString JSON_END_PORT_NUMBER = "endPortNumber";
const static QString JSON_CONNECTOR_POS_X = "connectorPosX";
const static QString JSON_CONNECTOR_POS_Y = "connectorPosY";
const static QString JSON_DST_CONNECTION_NAME = "dstConnectionName";

Project::Project() {
  QDir dir;
  m_filePath = dir.absolutePath() + "/" + DEFAULT_FILE_NAME;
}

Project::~Project() {
  delete m_scene;
}

void Project::init() {
  m_scene = new Scene();
}

bool Project::open(const QString& filePath) {
  QFile f(filePath);
  if (!f.open(QIODevice::ReadOnly)) {
    return false;
  }

  m_filePath = filePath;

  QByteArray data = f.readAll();
  fromJson(data);

  return true;
}

bool Project::save(const QString& filePath) {
  QFile f(filePath);
  if (!f.open(QIODevice::WriteOnly)) {
    return false;
  }

  m_filePath = filePath;

  QByteArray data = toJson();
  f.write(data);
  f.close();

  return true;
}

QString Project::filePath() const {
  return m_filePath;
}

QString Project::fileBaseName() const {
  QFileInfo info(m_filePath);
  return info.baseName();
}

QByteArray Project::toJson() {
  Scene* scene = Editor::getInstance()->project()->scene();

  QJsonArray nodeJsonArray;
  foreach (AbstractNode* node, scene->nodes()) {
    QJsonObject nodeJsonObj;
    nodeJsonObj[JSON_NAME] = node->name();
    nodeJsonObj[JSON_NODETYPE] = node->nodeType();
    nodeJsonObj[JSON_X] = node->pos().x();
    nodeJsonObj[JSON_Y] = node->pos().y();
    QJsonArray portJsonArray;
    foreach (Port* port, node->ports()) {
      QJsonObject portJsonObj;
      portJsonObj[JSON_PORT_NUMBER] = static_cast<int32_t>(port->number());
      portJsonObj[JSON_PORT_INVERTED] = port->isInvert();
      portJsonArray.append(portJsonObj);
    }
    nodeJsonObj[JSON_PORTS] = portJsonArray;

    nodeJsonArray.append(nodeJsonObj);
  }

  QJsonArray nodeToNodeConnectionJsonArray;
  QJsonArray nodeToConnectorConnectionJsonArray;
  foreach (Connection* connection, scene->connections()) {
    QJsonObject connectionJsonObj;
    connectionJsonObj[JSON_NAME] = connection->name();

    Port* startPort = connection->startPort();
    Port* endPort = connection->endPort();
    Connector* endConnector = connection->endConnector();
    if (endPort) {
      connectionJsonObj[JSON_START_NODE_NAME] = startPort->parentNode()->name();
      connectionJsonObj[JSON_START_PORT_NUMBER] = QString::number(startPort->number());
      connectionJsonObj[JSON_END_NODE_NAME] = endPort->parentNode()->name();
      connectionJsonObj[JSON_END_PORT_NUMBER] = QString::number(endPort->number());
      nodeToNodeConnectionJsonArray << connectionJsonObj;
    } else if (endConnector) {
      connectionJsonObj[JSON_START_NODE_NAME] = startPort->parentNode()->name();
      connectionJsonObj[JSON_START_PORT_NUMBER] = QString::number(startPort->number());
      connectionJsonObj[JSON_CONNECTOR_POS_X] = QString::number(endConnector->scenePos().x());
      connectionJsonObj[JSON_CONNECTOR_POS_Y] = QString::number(endConnector->scenePos().y());
      connectionJsonObj[JSON_DST_CONNECTION_NAME] = endConnector->dstConnection()->name();
      nodeToConnectorConnectionJsonArray << connectionJsonObj;
    }
  }

  QJsonObject jsonObj;
  jsonObj[JSON_NODE_NAME_VISIBLE] = m_nodeNameVisible;
  jsonObj[JSON_NODES] = nodeJsonArray;
  jsonObj[JSON_NODE_TO_NODE_CONNECTIONS] = nodeToNodeConnectionJsonArray;
  jsonObj[JSON_NODE_TO_CONNECTOR_CONNECTIONS] = nodeToConnectorConnectionJsonArray;

  QJsonDocument doc(jsonObj);

  return doc.toJson();
}

void Project::fromJson(const QByteArray& data) {
  QJsonDocument doc(QJsonDocument::fromJson(data));
  QJsonObject rootObj(doc.object());
  Scene* scene = Editor::getInstance()->project()->scene();

  // this property need to read before create nodes
  m_nodeNameVisible = rootObj[JSON_NODE_NAME_VISIBLE].toBool();

  QJsonArray nodeJsonObjs = rootObj[JSON_NODES].toArray();
  foreach (QJsonValue nodeJsonVal, nodeJsonObjs) {
    QString name = nodeJsonVal[JSON_NAME].toString();
    QString nodeType = nodeJsonVal[JSON_NODETYPE].toString();
    qreal x = nodeJsonVal[JSON_X].toDouble();
    qreal y = nodeJsonVal[JSON_Y].toDouble();

    AbstractNode* node = NodeFactory::getInstance()->createNode(nodeType, name);
    node->setNameTextVisible(m_nodeNameVisible);
    node->setName(name);

    foreach (QJsonValue portJsonValue, nodeJsonVal[JSON_PORTS].toArray()) {
      unsigned int portNum = portJsonValue[JSON_PORT_NUMBER].toInt();
      Port* port = node->port(portNum);
      if (portJsonValue[JSON_PORT_INVERTED].toBool()) {
        port->invert();
      }
    }

    scene->addNode(node, QPointF(x, y));
  }

  foreach (QJsonValue connectionJsonVal, rootObj[JSON_NODE_TO_NODE_CONNECTIONS].toArray()) {
    QString name = connectionJsonVal[JSON_NAME].toString();
    QString startNodeName = connectionJsonVal[JSON_START_NODE_NAME].toString();
    uint32_t startPortNumber = connectionJsonVal[JSON_START_PORT_NUMBER].toString().toInt();
    QString endNodeName = connectionJsonVal[JSON_END_NODE_NAME].toString();
    uint32_t endPortNumber = connectionJsonVal[JSON_END_PORT_NUMBER].toString().toInt();

    Connection* connection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
    connection->setName(name);
    scene->addConnection(connection, startNodeName, startPortNumber, endNodeName, endPortNumber);
  }

  foreach (QJsonValue connectionJsonVal, rootObj[JSON_NODE_TO_CONNECTOR_CONNECTIONS].toArray()) {
    QString name = connectionJsonVal[JSON_NAME].toString();
    QString startNodeName = connectionJsonVal[JSON_START_NODE_NAME].toString();
    uint32_t startPortNumber = connectionJsonVal[JSON_START_PORT_NUMBER].toString().toInt();
    QString dstConnectionName = connectionJsonVal[JSON_DST_CONNECTION_NAME].toString();
    qreal posX = connectionJsonVal[JSON_CONNECTOR_POS_X].toString().toDouble();
    qreal posY = connectionJsonVal[JSON_CONNECTOR_POS_Y].toString().toDouble();

    Connection* connection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
    connection->setName(name);
    Connector* endConnector = ConnectorFactory::getInstance()->createConnector(CONNECTOR);
    endConnector->setPos(posX, posY);
    scene->addConnection(connection, startNodeName, startPortNumber, endConnector, dstConnectionName);
  }
}

bool Project::nodeNameVisible() const {
  return m_nodeNameVisible;
}

void Project::setNodeNameVisible(bool nodeNameVisible) {
  m_nodeNameVisible = nodeNameVisible;
}

Scene* Project::scene() const {
  return m_scene;
}
