#include "AbstractAction.h"


AbstractAction::AbstractAction(QObject *parent) : QObject(parent)
{
}

AbstractAction::~AbstractAction()
{
}

QAction *AbstractAction::action()
{
    return m_action;
}

