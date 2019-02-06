#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Project.h"
#include "Editor.h"
#include "Scene.h"
#include "AbstractNode.h"
#include "NodeFactory.h"
#include "Connection.h"
#include "Port.h"


Project::Project()
{
}

Project::~Project()
{
}

void Project::init()
{
    m_scene = new Scene();
}

bool Project::open(const QString &filePath)
{
    QFile f(filePath);
    if(!f.open(QIODevice::ReadOnly)){
        return false;
    }

    m_filePath = filePath;

    QByteArray data = f.readAll();
    fromJson(data);

    return true;
}

bool Project::save(const QString &filePath)
{
    QFile f(filePath);
    if(!f.open(QIODevice::WriteOnly)){
        return false;
    }

    m_filePath = filePath;

    QByteArray data = toJson();
    f.write(data);
    f.close();

    return true;
}

QString Project::filePath() const
{
    return m_filePath;
}

QByteArray Project::toJson()
{
    Scene* scene = Editor::getInstance()->project()->scene();

    QJsonArray nodeJsonArray;
    foreach (AbstractNode* node, scene->nodes()) {
        QJsonObject nodeJsonObj;
        nodeJsonObj["name"]     = node->name();
        nodeJsonObj["nodetype"] = node->nodeType();
        nodeJsonObj["x"]        = node->pos().x();
        nodeJsonObj["y"]        = node->pos().y();

        nodeJsonArray.append(nodeJsonObj);
    }

    QJsonArray linkJsonArray;
    foreach (Connection* connection, scene->connections()) {
        QJsonObject connectionJsonObj;
        Port* startPort = connection->startPort();
        Port* endPort   = connection->endPort();

        connectionJsonObj["startNodeName"]   = startPort->parentNode()->name();
        connectionJsonObj["startPortNumber"] = QString::number(startPort->number());
        connectionJsonObj["endNodeName"]     = endPort->parentNode()->name();
        connectionJsonObj["endPortNumber"]   = QString::number(endPort->number());

        linkJsonArray.append(connectionJsonObj);
    }

    QJsonObject jsonObj;
    jsonObj["nodes"] = nodeJsonArray;
    jsonObj["link"]  = linkJsonArray;

    QJsonDocument doc(jsonObj);

    return doc.toJson();
}

void Project::fromJson(const QByteArray &data)
{
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject rootObj(doc.object());
    Scene* scene = Editor::getInstance()->project()->scene();

    QJsonArray nodeJsonObjs = rootObj["nodes"].toArray();
    foreach (QJsonValue nodeJsonVal, nodeJsonObjs) {

        QString name     = nodeJsonVal["name"].toString();
        QString nodeType = nodeJsonVal["nodetype"].toString();
        qreal   x        = nodeJsonVal["x"].toDouble();
        qreal   y        = nodeJsonVal["y"].toDouble();

        AbstractNode* node = NodeFactory::getInstance()->createNode(nodeType, name);
        node->setName(name);

        scene->addNode(node, QPointF(x, y));
    }

    QJsonArray linkJsonObjs = rootObj["link"].toArray();
    foreach (QJsonValue linkJsonVal, linkJsonObjs) {
        QString  startNodeName   = linkJsonVal["startNodeName"].toString();
        uint32_t startPortNumber = linkJsonVal["startPortNumber"].toString().toInt();
        QString  endNodeName     = linkJsonVal["endNodeName"].toString();
        uint32_t endPortNumber   = linkJsonVal["endPortNumber"].toString().toInt();

        scene->addConnection(startNodeName, startPortNumber, endNodeName, endPortNumber);
    }
}

Scene *Project::scene() const
{
    return m_scene;
}
