#include "Editor.h"
#include <QGraphicsView>
#include "Scene.h"
#include "Project.h"
#include "AbstractAction.h"

Editor* Editor::getInstance()
{
    static Editor s;
    return &s;
}

void Editor::init()
{
    m_project = new Project();
    m_project->init();

    Project* newProject = Editor::getInstance()->project();
    Scene*   newScene   = newProject->scene();
    m_graphicsView->setScene(newScene);
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

Project *Editor::project() const
{
    return m_project;
}

void Editor::setGraphicsView(QGraphicsView *graphicsView)
{
    m_graphicsView = graphicsView;
}

Editor::Editor():
    m_graphicsView()
{
}

Editor::~Editor()
{
}
