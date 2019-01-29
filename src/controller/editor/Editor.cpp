#include "Editor.h"
#include "AbstractAction.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

AbstractAction *Editor::action(QString &name)
{
    foreach (AbstractAction* action, m_actions) {
        if(name == action->name()){
            return action;
        }
    }
    return nullptr;
}

Scene *Editor::scene() const
{
    return m_scene;
}
