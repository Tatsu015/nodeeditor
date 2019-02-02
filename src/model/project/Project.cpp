#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Project.h"
#include "Editor.h"
#include "Scene.h"
#include "Node.h"
#include "HiddenNode.h"

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

    f.write(toJson());
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
    foreach (Node* node, scene->nodes()) {
        QJsonObject nodeJsonObj;
        nodeJsonObj["name"] = node->name();
        nodeJsonObj["x"]    = node->pos().x();
        nodeJsonObj["y"]    = node->pos().y();

        nodeJsonArray.append(nodeJsonObj);
    }

    QJsonObject jsonObj;
    jsonObj["nodes"] = nodeJsonArray;

    QJsonDocument doc(jsonObj);

    return doc.toJson();
}

void Project::fromJson(const QByteArray &data)
{
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject rootObj(doc.object());
    QJsonArray nodeJsonObjs = rootObj["nodes"].toArray();

    Scene* scene = Editor::getInstance()->project()->scene();
    foreach (QJsonValue nodeJsonVal, nodeJsonObjs) {
        HiddenNode* node = new HiddenNode();

        QString name = nodeJsonVal["name"].toString();
        qreal   x    = nodeJsonVal["x"].toDouble();
        qreal   y    = nodeJsonVal["y"].toDouble();

        node->setName(name);
        node->setPos(x, y);

        scene->addNode(node);
    }
}

Scene *Project::scene() const
{
    return m_scene;
}
