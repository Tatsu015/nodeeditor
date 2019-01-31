#include "Open.h"
#include <QAction>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include "Editor.h"
#include <QJsonDocument>
#include "Scene.h"
#include "Node.h"
#include "HiddenNode.h"

const QString Open::ACTION_OPEN = "Open";

Open::Open(QObject *parent):
    AbstractAction(parent)
{
    m_action = new QAction(ACTION_OPEN);
    connect(m_action, &QAction::triggered, this, &Open::execute);
}

Open::~Open()
{
}

QAction *Open::action()
{
    return m_action;
}

QString Open::name()
{
    return ACTION_OPEN;
}

void Open::execute()
{
    QFile file("test.json");
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data = file.readAll();
    fromJson(data);
}

void Open::fromJson(const QByteArray& data)
{
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject rootObj(doc.object());
    QJsonArray nodeJsonObjs = rootObj["nodes"].toArray();

    Scene* scene = Editor::getInstance()->scene();
    foreach (QJsonValue nodeJsonVal, nodeJsonObjs) {
        qDebug() << nodeJsonVal;
        HiddenNode* node = new HiddenNode();

        QString name = nodeJsonVal["name"].toString();
        qreal   x    = nodeJsonVal["x"].toDouble();
        qreal   y    = nodeJsonVal["y"].toDouble();

        node->setName(name);
        node->setPos(x, y);

        scene->addNode(node);
    }
}
