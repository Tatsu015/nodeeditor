#include "Editor.h"
#include <QGraphicsView>
#include <QUndoStack>
#include "AndNode.h"
#include "Connection.h"
#include "ConnectionCreateTool.h"
#include "ConnectionFactory.h"
#include "Define.h"
#include "InNode.h"
#include "NodeEditTool.h"
#include "NodeFactory.h"
#include "OrNode.h"
#include "OutNode.h"
#include "Project.h"
#include "Scene.h"

Editor *Editor::getInstance() {
  static Editor s;
  return &s;
}

void Editor::init() {
  initFactory();
  initTool();
  initUndoStack();

  resetProject();
}

void Editor::reset() {
  resetProject();
  m_graphicsView->setScene(m_project->scene());
}

Project *Editor::project() const { return m_project; }

void Editor::setGraphicsView(QGraphicsView *graphicsView) { m_graphicsView = graphicsView; }

AbstractTool *Editor::tool(const QString &toolName) const { return m_tools[toolName]; }

AbstractTool *Editor::activeTool() const { return m_activeTool; }

void Editor::changeActiveTool(const QString &toolName) { m_activeTool = m_tools[toolName]; }

void Editor::changeDefaultTool() { changeActiveTool(TOOL_NODE_CREATE); }

void Editor::addCommand(QUndoCommand *undoCommand) {
  m_undoStack->push(undoCommand);
  QString projectNameWithEdited = m_project->fileBaseName();
  if (0 != m_undoStack->count()) {
    projectNameWithEdited += "*";
  }
  projectNameChanged(projectNameWithEdited);
}

void Editor::resetProject() {
  delete project();
  m_project = new Project();
  m_project->init();
}

void Editor::addTool(AbstractTool *tool) {
  QString name = tool->name();
  m_tools[name] = tool;
}

QUndoStack *Editor::undoStack() const { return m_undoStack; }

void Editor::initFactory() {
  NodeFactory::getInstance()->addNode(new InNode());
  NodeFactory::getInstance()->addNode(new OutNode());
  NodeFactory::getInstance()->addNode(new AndNode());
  NodeFactory::getInstance()->addNode(new OrNode());

  ConnectionFactory::getInstance()->addConnection(new Connection());
}

void Editor::initTool() {
  addTool(new NodeEditTool());
  addTool(new ConnectionCreateTool());

  // set default tool
  m_activeTool = m_tools[TOOL_NODE_CREATE];
}

void Editor::initUndoStack() { m_undoStack = new QUndoStack(); }

Editor::Editor(QObject *parent) : QObject(parent), m_graphicsView() {}

Editor::~Editor() {}
