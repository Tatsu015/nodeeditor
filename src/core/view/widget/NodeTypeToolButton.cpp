#include "NodeTypeToolButton.h"
#include "Define.h"
#include "Editor.h"
#include "NodeEditTool.h"
#include "NodeFactory.h"

NodeTypeToolButton::NodeTypeToolButton(QString& nodeName, QWidget* parent) : QToolButton(parent) {
  setText(nodeName);
  setIcon(NodeFactory::getInstance()->createIcon(nodeName));
  connect(this, &NodeTypeToolButton::clicked, this, &NodeTypeToolButton::onChangeNodeType);
}

NodeTypeToolButton::~NodeTypeToolButton() {
}

void NodeTypeToolButton::onChangeNodeType() {
  NodeEditTool* tool = dynamic_cast<NodeEditTool*>(Editor::getInstance()->tool(TOOL_NODE_EDIT));
  tool->setActiveNodeType(text());
}
