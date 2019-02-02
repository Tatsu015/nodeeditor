#include "Open.h"
#include <QAction>
#include <QFile>
#include <QDebug>


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
}
