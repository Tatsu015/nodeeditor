#include "OpenAction.h"
#include <QAction>
#include <QFile>
#include <QDebug>
#include "Editor.h"
#include "Project.h"
#include "Define.h"


OpenAction::OpenAction(QObject *parent):
    AbstractAction(parent)
{
    m_action = new QAction(ACTION_OPEN);
    connect(m_action, &QAction::triggered, this, &OpenAction::execute);
}

OpenAction::~OpenAction()
{
}

QString OpenAction::name()
{
    return ACTION_OPEN;
}

void OpenAction::execute()
{
    Editor::getInstance()->project()->open("test.json");
//    QFile file("test.json");
//    if(!file.open(QIODevice::ReadOnly)){
//        return;
//    }
}
