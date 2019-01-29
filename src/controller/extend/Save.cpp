#include "Save.h"
#include "Editor.h"

Save::Save(QObject *parent):
    AbstractAction(parent)
{
}

Save::~Save()
{
}

QAction *Save::action()
{
    return m_action;
}

void Save::execute()
{

}
