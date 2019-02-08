#include "Editor.h"
#include <QGraphicsView>
#include "AbstractAction.h"
#include "ConnectionCreateTool.h"
#include "Define.h"
#include "NodeEditTool.h"
#include "Project.h"
#include "Scene.h"
#include "NodeFactory.h"
#include "OpenAction.h"
#include "OutNode.h"
#include "OrNode.h"
#include "SaveAction.h"
#include "AnalyzeCircuitAction.h"
#include "AndNode.h"
#include "InNode.h"
#include "ConnectionFactory.h"
#include "Connection.h"


Editor *Editor::getInstance() {
  static Editor s;
  return &s;
}

void Editor::init() {
  NodeFactory::getInstance()->addNode(new InNode());
  NodeFactory::getInstance()->addNode(new OutNode());
  NodeFactory::getInstance()->addNode(new AndNode());
  NodeFactory::getInstance()->addNode(new OrNode());

  ConnectionFactory::getInstance()->addConnection(new Connection());

  // setup action
  Editor::getInstance()->addAction(new OpenAction());
  Editor::getInstance()->addAction(new SaveAction());
  Editor::getInstance()->addAction(new AnalyzeCircuitAction());

  resetProject();

  initTool();
}

void Editor::reset()
{
  resetProject();
  m_graphicsView->setScene(m_project->scene());
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

void Editor::resetProject()
{
  delete project();
  m_project = new Project();
  m_project->init();
}

void Editor::addTool(AbstractTool *tool) {
  QString name = tool->name();
  m_tools[name] = tool;
}

void Editor::initTool() {
  addTool(new NodeEditTool());
  addTool(new ConnectionCreateTool());

  // set default tool
  m_activeTool = m_tools[TOOL_NODE_CREATE];
}

Editor::Editor() : m_graphicsView() {}

Editor::~Editor() {}
