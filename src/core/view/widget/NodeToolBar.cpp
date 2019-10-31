#include "NodeToolBar.h"
#include "FunctionBlockToolButton.h"
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

void NodeToolBar::addToolButton(FunctionBlockToolButton* toolButton) {
  m_functionBlockToolButton = toolButton;
  addWidget(toolButton);
  connect(toolButton, &FunctionBlockToolButton::clicked, this, &NodeToolBar::onChangeTool);
}

void NodeToolBar::removeToolBarAction(QAction* action) {
  removeAction(action);
  disconnect(action, &QAction::triggered, this, &NodeToolBar::onChangeTool);
}

void NodeToolBar::onChangeTool() {
  if (dynamic_cast<QAction*>(sender())) {
    QAction* action = dynamic_cast<QAction*>(sender());
    changeTool(action);
  } else if (dynamic_cast<FunctionBlockToolButton*>(sender())) {
    FunctionBlockToolButton* toolButton = dynamic_cast<FunctionBlockToolButton*>(sender());
    changeTool(toolButton);
  }
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
  if (m_functionBlockToolButton->hasAction()) {
    m_functionBlockToolButton->setEnabled(true);
  } else {
    m_functionBlockToolButton->setEnabled(false);
  }
  activeAction->setEnabled(false);
}

void NodeToolBar::changeTool(FunctionBlockToolButton* toolButton) {
  //  if (0 >= toolButton->actions().count()) {
  //    return;
  //  }
  m_NodeEditTool->setActiveNodeType(toolButton->text());
  toolButton->setEnabled(true);
  foreach (QAction* action, actions()) { action->setEnabled(true); }
  m_functionBlockToolButton->setEnabled(false);
}
