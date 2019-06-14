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
  m_NodeEditTool->setActiveNodeType(action->text());
}

void NodeToolBar::setNodeEditTool(NodeEditTool* NodeEditTool) {
  m_NodeEditTool = NodeEditTool;
}
