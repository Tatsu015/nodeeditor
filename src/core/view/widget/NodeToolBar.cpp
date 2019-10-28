#include "NodeToolBar.h"
#include "NodeEditTool.h"
#include "Sheet.h"

NodeToolBar::NodeToolBar(QWidget* parent) : QToolBar(parent) {
}

NodeToolBar::~NodeToolBar() {
}

void NodeToolBar::addToolBarAction(QAction* action) {
  addAction(action);
  connect(action, &QAction::triggered, this, &NodeToolBar::onChangeTool);
}

void NodeToolBar::removeToolBarAction(QAction* action) {
  removeAction(action);
  disconnect(action, &QAction::triggered, this, &NodeToolBar::onChangeTool);
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

void NodeToolBar::addSheet(Sheet* sheet) {
  QAction* action = new QAction(sheet->name());
  m_actions[sheet->name()] = action;
  addToolBarAction(action);
}

void NodeToolBar::changeSheet(Sheet* sheet) {
}

void NodeToolBar::removeSheet(Sheet* sheet) {
  QAction* action = m_actions[sheet->name()];
  removeToolBarAction(action);
}

void NodeToolBar::changeTool(QAction* activeAction) {
  m_NodeEditTool->setActiveNodeType(activeAction->text());
  foreach (QAction* action, actions()) { action->setEnabled(true); }
  activeAction->setEnabled(false);
}
