#include "NodeToolBar.h"
#include "NodeCreateTool.h"

NodeToolBar::NodeToolBar(QWidget* parent) : QToolBar(parent) {}

NodeToolBar::~NodeToolBar() {}

void NodeToolBar::addToolBarAction(const QString& nodeType) {
  QAction* action = new QAction(nodeType);
  addAction(action);
  connect(action, &QAction::triggered, this, &NodeToolBar::onChangeTool);
}

void NodeToolBar::onChangeTool() {
  QAction* action = dynamic_cast<QAction*>(sender());
  m_nodeCreationTool->setActiveNodeType(action->text());
}

void NodeToolBar::setNodeCreationTool(NodeCreateTool* nodeCreationTool) { m_nodeCreationTool = nodeCreationTool; }
