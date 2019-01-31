#include "Editor.h"
#include "Scene.h"
#include "AbstractAction.h"

Editor* Editor::getInstance()
{
    static Editor s;
    return &s;
}

AbstractAction *Editor::action(const QString& name)
{
    foreach (AbstractAction* action, m_actions) {
        if(name == action->name()){
            return action;
        }
    }
    return nullptr;
}

void Editor::addAction(AbstractAction *action)
{
    m_actions.append(action);
}

Scene *Editor::scene() const
{
    return m_scene;
}

Editor::Editor():
    m_scene(new Scene())
{
}

Editor::~Editor()
{
}
