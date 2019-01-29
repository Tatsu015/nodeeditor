#include "AbstractAction.h"

AbstractAction::AbstractAction(QObject *parent) : QObject(parent)
{
}

AbstractAction::~AbstractAction()
{
}

QString AbstractAction::name()
{
    return "";
}
