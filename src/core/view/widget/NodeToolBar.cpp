#include "NodeToolBar.h"
#include "NodeEditTool.h"

NodeToolBar::NodeToolBar(QWidget* parent) : QToolBar(parent) {
}

NodeToolBar::~NodeToolBar() {
}

void NodeToolBar::addToolBarAction(const QString& nodeType) {
  QAction* action = new QAction(nodeType);
  addAction(action);
  connect(action, &QAction::triggered, this, &NodeToolBar::onChangeTool);
}

void NodeToolBar::onChangeTool() {
  QAction* action = dynamic_cast<QAction*>(sender());
  changeTool(action);
}

void NodeToolBar::setNodeEditTool(NodeEditTool* NodeEditTool) {
  m_NodeEditTool = NodeEditTool;
}

void NodeToolBar::changeDefaultTool() {
  changeTool(actions().first());
}

void NodeToolBar::changeTool(QAction* activeAction) {
  m_NodeEditTool->setActiveNodeType(activeAction->text());
  foreach (QAction* action, actions()) { action->setEnabled(true); }
  activeAction->setEnabled(false);
}
