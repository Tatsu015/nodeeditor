#include "Editor.h"
#include <QGraphicsView>
#include "AbstractAction.h"
#include "ConnectionCreationTool.h"
#include "Define.h"
#include "NodeCreateTool.h"
#include "Project.h"
#include "Scene.h"

Editor *Editor::getInstance() {
  static Editor s;
  return &s;
}

void Editor::init() {
  m_project = new Project();
  m_project->init();

  Project *newProject = Editor::getInstance()->project();
  Scene *newScene = newProject->scene();
  m_graphicsView->setScene(newScene);

  initTool();
}

AbstractAction *Editor::action(const QString &name) {
  foreach (AbstractAction *action, m_actions) {
    if (name == action->name()) {
      return action;
    }
  }
  return nullptr;
}

void Editor::addAction(AbstractAction *action) { m_actions.append(action); }

Project *Editor::project() const { return m_project; }

void Editor::setGraphicsView(QGraphicsView *graphicsView) { m_graphicsView = graphicsView; }

AbstractTool *Editor::tool(const QString &toolName) const { return m_tools[toolName]; }

AbstractTool *Editor::activeTool() const { return m_activeTool; }

void Editor::changeActiveTool(const QString &toolName) { m_activeTool = m_tools[toolName]; }

void Editor::changeDefaultTool() { changeActiveTool(TOOL_NODE_CREATE); }

void Editor::addTool(AbstractTool *tool) {
  QString name = tool->name();
  m_tools[name] = tool;
}

void Editor::initTool() {
  addTool(new NodeCreateTool());
  addTool(new ConnectionCreationTool());

  // set default tool
  m_activeTool = m_tools[TOOL_NODE_CREATE];
}

Editor::Editor() : m_graphicsView() {}

Editor::~Editor() {}
