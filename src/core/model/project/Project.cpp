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
#include "ProjectObserver.h"
#include "Scene.h"
#include "Sheet.h"
#include "SheetFactory.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

const static QString DEFAULT_FILE_NAME = "Undefined." + APP_EXTENSION;
const static QString JSON_NODE_NAME_VISIBLE = "nodeNameVisible";
const static QString JSON_ID = "id";
const static QString JSON_SHEETS = "sheets";
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
  m_scene = new Scene();
}

Project::~Project() {
  delete m_scene;
}

void Project::run() {
  Sheet* firstSheet = SheetFactory::getInstance()->createSheet();
  m_activeSheet = firstSheet;
  addSheet(firstSheet);
  m_scene->setSheet(firstSheet);
}

void Project::reset() {
  foreach (Sheet* sheet, m_sheets) { removeSheet(sheet); }
}

bool Project::open(const QString& filePath) {
  QFile f(filePath);
  if (!f.open(QIODevice::ReadOnly)) {
    return false;
  }

  m_filePath = filePath;

  foreach (Sheet* sheet, m_sheets) { removeSheet(sheet); }
  m_activeSheet = nullptr;

  QByteArray data = f.readAll();
  fromJson(data);

  setActiveSheet(m_sheets.first());

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

QList<Sheet*> Project::sheets() const {
  return m_sheets;
}

Sheet* Project::sheet(const QString& sheetName) const {
  foreach (Sheet* sheet, m_sheets) {
    if (sheetName == sheet->name()) {
      return sheet;
    }
  }
  return nullptr;
}

void Project::addSheet(Sheet* sheet) {
  m_sheets << sheet;
  m_activeSheet = sheet;
  foreach (ProjectObserver* projectObserver, m_projectObservers) { projectObserver->addSheet(sheet); }
}

void Project::removeSheet(Sheet* sheet) {
  m_sheets.removeOne(sheet);
  foreach (ProjectObserver* projectObserver, m_projectObservers) { projectObserver->removeSheet(sheet); }
}

void Project::removeSheet(const QString& sheetName) {
  Sheet* willRemoveSheet = sheet(sheetName);
  if (willRemoveSheet) {
    removeSheet(willRemoveSheet);
  }
}

Sheet* Project::activeSheet() const {
  return m_activeSheet;
}

void Project::setActiveSheet(Sheet* activeSheet) {
  m_activeSheet = activeSheet;
  foreach (ProjectObserver* projectObserver, m_projectObservers) { projectObserver->changeSheet(m_activeSheet); }
  m_scene->setSheet(m_activeSheet);
}

void Project::setActiveSheet(const QString& sheetName) {
  Sheet* willActiveSheet = sheet(sheetName);
  if (willActiveSheet) {
    setActiveSheet(willActiveSheet);
  }
}

void Project::changeActiveSheet(const int32_t index) {
  Sheet* willActiveSheet = m_sheets.at(index);
  if (willActiveSheet) {
    changeActiveSheet(willActiveSheet->name());
  }
}

void Project::changeActiveSheet(const QString& sheetName) {
  m_activeSheet = sheet(sheetName);
  m_scene->changeSheet(m_activeSheet);
  foreach (ProjectObserver* projectObserver, m_projectObservers) { projectObserver->changeSheet(m_activeSheet); }
  // need to update because when after change sheet, graphics trash remain...
  m_scene->update();
}

void Project::addObserver(ProjectObserver* projectObserver) {
  m_projectObservers << projectObserver;
}

QByteArray Project::toJson() {
  QJsonArray sheetJsonArray;

  foreach (Sheet* sheet, m_sheets) {
    QJsonObject sheetJsonObj;
    sheetJsonObj[JSON_NAME] = sheet->name();
    sheetJsonObj[JSON_ID] = sheet->id();

    QJsonArray nodeJsonArray;
    foreach (AbstractNode* node, sheet->nodes()) {
      QJsonObject nodeJsonObj;
      nodeJsonObj[JSON_ID] = node->id();
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
    foreach (Connection* connection, sheet->connections()) {
      QJsonObject connectionJsonObj;
      connectionJsonObj[JSON_ID] = connection->id();
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

    sheetJsonObj[JSON_NODES] = nodeJsonArray;
    sheetJsonObj[JSON_NODE_TO_NODE_CONNECTIONS] = nodeToNodeConnectionJsonArray;
    sheetJsonObj[JSON_NODE_TO_CONNECTOR_CONNECTIONS] = nodeToConnectorConnectionJsonArray;

    sheetJsonArray.append(sheetJsonObj);
  }

  QJsonObject jsonObj;
  jsonObj[JSON_NODE_NAME_VISIBLE] = m_nodeNameVisible;
  jsonObj[JSON_SHEETS] = sheetJsonArray;

  QJsonDocument doc(jsonObj);

  return doc.toJson();
}

void Project::fromJson(const QByteArray& data) {
  QJsonDocument doc(QJsonDocument::fromJson(data));
  QJsonObject rootObj(doc.object());
  Scene* scene = Editor::getInstance()->project()->scene();

  // this property need to read before create nodes
  m_nodeNameVisible = rootObj[JSON_NODE_NAME_VISIBLE].toBool();

  foreach (QJsonValue sheetJsonVal, rootObj[JSON_SHEETS].toArray()) {
    Sheet* sheet = SheetFactory::getInstance()->createSheet();
    sheet->setName(sheetJsonVal[JSON_NAME].toString());
    addSheet(sheet);

    foreach (QJsonValue nodeJsonVal, sheetJsonVal[JSON_NODES].toArray()) {
      QString name = nodeJsonVal[JSON_NAME].toString();
      QString id = nodeJsonVal[JSON_ID].toString();
      QString nodeType = nodeJsonVal[JSON_NODETYPE].toString();
      qreal x = nodeJsonVal[JSON_X].toDouble();
      qreal y = nodeJsonVal[JSON_Y].toDouble();

      AbstractNode* node = NodeFactory::getInstance()->createNode(sheet, nodeType, name, id);
      node->setNameTextVisible(m_nodeNameVisible);
      node->setName(name);
      node->setPos(x, y);

      foreach (QJsonValue portJsonValue, nodeJsonVal[JSON_PORTS].toArray()) {
        unsigned int portNum = portJsonValue[JSON_PORT_NUMBER].toInt();
        Port* port = node->port(portNum);
        port->invert(portJsonValue[JSON_PORT_INVERTED].toBool());
      }

      sheet->addNode(node);
    }

    foreach (QJsonValue connectionJsonVal, sheetJsonVal[JSON_NODE_TO_NODE_CONNECTIONS].toArray()) {
      QString name = connectionJsonVal[JSON_NAME].toString();
      QString id = connectionJsonVal[JSON_ID].toString();
      QString startNodeName = connectionJsonVal[JSON_START_NODE_NAME].toString();
      uint32_t startPortNumber = connectionJsonVal[JSON_START_PORT_NUMBER].toString().toInt();
      QString endNodeName = connectionJsonVal[JSON_END_NODE_NAME].toString();
      uint32_t endPortNumber = connectionJsonVal[JSON_END_PORT_NUMBER].toString().toInt();

      Connection* connection = ConnectionFactory::getInstance()->createConnection(sheet, CONNECTION, name, id);
      AbstractNode* startNode = sheet->node(startNodeName);
      Port* startPort = startNode->port(startPortNumber);
      AbstractNode* endNode = sheet->node(endNodeName);
      Port* endPort = endNode->port(endPortNumber);

      connection->setName(name);
      connection->setStartPort(startPort);
      startPort->addConnection(connection);
      connection->setEndPort(endPort);
      endPort->addConnection(connection);

      sheet->addConnection(connection);
    }

    foreach (QJsonValue connectionJsonVal, sheetJsonVal[JSON_NODE_TO_CONNECTOR_CONNECTIONS].toArray()) {
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
      scene->addRect(connectorPosX, connectorPosY, 10, 10);
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

      sheet->addConnection(connection);
    }
  }
  setActiveSheet(m_sheets.first()->name());
}

bool Project::nodeNameVisible() const {
  return m_nodeNameVisible;
}

void Project::setNodeNameVisible(bool nodeNameVisible) {
  m_nodeNameVisible = nodeNameVisible;
}

void Project::takeOver(Project* project) {
  m_projectObservers = project->m_projectObservers;
  m_nodeNameVisible = project->m_nodeNameVisible;
}

Scene* Project::scene() const {
  return m_scene;
}
