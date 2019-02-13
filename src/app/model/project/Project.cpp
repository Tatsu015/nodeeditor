#include "Project.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>
#include "AbstractNode.h"
#include "Connection.h"
#include "Editor.h"
#include "NodeFactory.h"
#include "Port.h"
#include "Scene.h"

const static QString JSON_NODES = "nodeas";
const static QString JSON_LINKS = "links";
const static QString JSON_NAME = "name";
const static QString JSON_NODETYPE = "nodetype";
const static QString JSON_X = "x";
const static QString JSON_Y = "y";
const static QString JSON_START_NODE_NAME = "startNodeName";
const static QString JSON_START_PORT_NUMBER = "startPortNumber";
const static QString JSON_END_NODE_NAME =   "endNodeName";
const static QString JSON_END_PORT_NUMBER = "endPortNumber";

Project::Project() {}

Project::~Project() { delete m_scene; }

void Project::init() { m_scene = new Scene(); }

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

QString Project::filePath() const { return m_filePath; }

QString Project::fileBaseName() const
{
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

    nodeJsonArray.append(nodeJsonObj);
  }

  QJsonArray linkJsonArray;
  foreach (Connection* connection, scene->connections()) {
    QJsonObject connectionJsonObj;
    Port* startPort = connection->startPort();
    Port* endPort = connection->endPort();

    connectionJsonObj[JSON_START_NODE_NAME] = startPort->parentNode()->name();
    connectionJsonObj[JSON_START_PORT_NUMBER] = QString::number(startPort->number());
    connectionJsonObj[JSON_END_NODE_NAME] = endPort->parentNode()->name();
    connectionJsonObj[JSON_END_PORT_NUMBER] = QString::number(endPort->number());

    linkJsonArray.append(connectionJsonObj);
  }

  QJsonObject jsonObj;
  jsonObj[JSON_NODES] = nodeJsonArray;
  jsonObj[JSON_LINKS] = linkJsonArray;

  QJsonDocument doc(jsonObj);

  return doc.toJson();
}

void Project::fromJson(const QByteArray& data) {
  QJsonDocument doc(QJsonDocument::fromJson(data));
  QJsonObject rootObj(doc.object());
  Scene* scene = Editor::getInstance()->project()->scene();

  QJsonArray nodeJsonObjs = rootObj[JSON_NODES].toArray();
  foreach (QJsonValue nodeJsonVal, nodeJsonObjs) {
    QString name = nodeJsonVal[JSON_NAME].toString();
    QString nodeType = nodeJsonVal[JSON_NODETYPE].toString();
    qreal x = nodeJsonVal[JSON_X].toDouble();
    qreal y = nodeJsonVal[JSON_Y].toDouble();

    AbstractNode* node = NodeFactory::getInstance()->createNode(nodeType, name);
    node->setName(name);

    scene->addNode(node, QPointF(x, y));
  }

  QJsonArray linkJsonObjs = rootObj[JSON_LINKS].toArray();
  foreach (QJsonValue linkJsonVal, linkJsonObjs) {
    QString startNodeName = linkJsonVal[JSON_START_NODE_NAME].toString();
    uint32_t startPortNumber = linkJsonVal[JSON_START_PORT_NUMBER].toString().toInt();
    QString endNodeName = linkJsonVal[JSON_END_NODE_NAME].toString();
    uint32_t endPortNumber = linkJsonVal[JSON_END_PORT_NUMBER].toString().toInt();

    scene->addConnection(startNodeName, startPortNumber, endNodeName, endPortNumber);
  }
}

Scene* Project::scene() const { return m_scene; }
