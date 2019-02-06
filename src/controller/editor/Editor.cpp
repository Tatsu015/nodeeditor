#include "Editor.h"
#include <QGraphicsView>
#include "Scene.h"
#include "Project.h"
#include "AbstractAction.h"

#include "NodeCreateTool.h"
#include "ConnectionCreationTool.h"

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

    m_tools["NODE"]       = new NodeCreateTool();
    m_tools["CONNECTION"] = new ConnectionCreationTool();

    m_activeTool = m_tools["NODE"];
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

AbstractTool *Editor::tool(const QString &toolName) const
{
    return m_tools[toolName];
}

AbstractTool *Editor::activeTool() const
{
    return m_activeTool;
}

void Editor::changeActiveTool(const QString &toolName)
{
    m_activeTool = m_tools[toolName];
}

Editor::Editor():
    m_graphicsView()
{
}

Editor::~Editor()
{
}
