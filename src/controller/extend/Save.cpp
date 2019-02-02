#include "Save.h"
#include <QAction>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "Editor.h"
#include <QJsonDocument>
#include "Scene.h"
#include "Node.h"

const QString Save::ACTION_SAVE = "Save";

Save::Save(QObject *parent):
    AbstractAction(parent)
{
    m_action = new QAction(ACTION_SAVE);
    connect(m_action, &QAction::triggered, this, &Save::execute);
}

Save::~Save()
{
}

QAction *Save::action()
{
    return m_action;
}

QString Save::name()
{
    return ACTION_SAVE;
}

void Save::execute()
{
}

