#include "SaveAction.h"
#include <QAction>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "Editor.h"
#include <QJsonDocument>
#include "AbstractNode.h"
#include "Project.h"

const QString SaveAction::ACTION_SAVE = "Save";

SaveAction::SaveAction(QObject *parent):
    AbstractAction(parent)
{
    m_action = new QAction(ACTION_SAVE);
    connect(m_action, &QAction::triggered, this, &SaveAction::execute);
}

SaveAction::~SaveAction()
{
}

QAction *SaveAction::action()
{
    return m_action;
}

QString SaveAction::name()
{
    return ACTION_SAVE;
}

void SaveAction::execute()
{
    Editor::getInstance()->project()->save("test.json");
}

