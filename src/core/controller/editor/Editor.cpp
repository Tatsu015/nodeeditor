#include "Editor.h"
#include "AndNode.h"
#include "ConnectionCreateTool.h"
#include "ConnectionFactory.h"
#include "ConnectionReconnectTool.h"
#include "Connector.h"
#include "ConnectorFactory.h"
#include "Define.h"
#include "ElbowConnection.h"
#include "FunctionBlockNode.h"
#include "InNode.h"
#include "NodeEditTool.h"
#include "NodeFactory.h"
#include "NotNode.h"
#include "OrNode.h"
#include "OutNode.h"
#include "PluginLoader.h"
#include "PolylineConnection.h"
#include "Project.h"
#include "Scene.h"
#include "SheetFactory.h"
#include "SheetJumpTool.h"
#include "SystemConfig.h"
#include <QGraphicsView>
#include <QUndoStack>

Editor* Editor::getInstance() {
  static Editor s;
  return &s;
}

void Editor::init() {
  loadSystemConfig("../config/system.conf");
  initFactory();
  initTool();
  initUndoStack();

  m_project = new Project();
}

void Editor::run() {
}

Project* Editor::project() const {
  return m_project;
}

void Editor::changeProject(Project* project) {
  m_project = project;
  m_graphicsView->setScene(project->scene());
}

void Editor::setGraphicsView(QGraphicsView* graphicsView) {
  m_graphicsView = graphicsView;
}

AbstractTool* Editor::tool(const QString& toolName) const {
  return m_tools[toolName];
}

AbstractTool* Editor::activeTool() const {
  return m_activeTool;
}

void Editor::changeActiveTool(const QString& toolName) {
  m_activeTool = m_tools[toolName];
}

void Editor::changeDefaultTool() {
  changeActiveTool(TOOL_NODE_EDIT);
}

void Editor::addCommand(QUndoCommand* undoCommand) {
  m_undoStack->push(undoCommand);
  QString projectNameWithEdited = m_project->fileBaseName();
  if (0 != m_undoStack->count()) {
    projectNameWithEdited += "*";
  }
  projectNameChanged(projectNameWithEdited);
}

void Editor::addTool(AbstractTool* tool) {
  QString name = tool->name();
  m_tools[name] = tool;
}

QUndoStack* Editor::undoStack() const {
  return m_undoStack;
}

void Editor::initFactory() {
  NodeFactory::getInstance()->addNode(new InNode());
  NodeFactory::getInstance()->addNode(new OutNode());
  NodeFactory::getInstance()->addNode(new NotNode());
  NodeFactory::getInstance()->addNode(new AndNode());
  NodeFactory::getInstance()->addNode(new OrNode());

  ConnectionFactory::getInstance()->addConnection(new ElbowConnection());
  ConnectionFactory::getInstance()->addConnection(new PolylineConnection());

  ConnectorFactory::getInstance()->addConnector(new Connector());
}

void Editor::initTool() {
  addTool(new NodeEditTool());
  addTool(new ConnectionCreateTool());
  addTool(new ConnectionReconnectTool());
  addTool(new SheetJumpTool());

  // set default tool
  m_activeTool = m_tools[TOOL_NODE_EDIT];
}

void Editor::initUndoStack() {
  m_undoStack = new QUndoStack();
}

Editor::Editor(QObject* parent) : QObject(parent), m_graphicsView() {
}

Editor::~Editor() {
}
