#include "FlipFlopNode.h"
#include "Define.h"
#include "Port.h"
#include <QBrush>
#include <QFont>
#include <QPen>

const static QString NODE_FLIPFLOP = "FlipFlop";

FlipFlopNode::FlipFlopNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_FLIPFLOP;
  m_io = Hidden;
  m_maxInputPortCount = 2;
  m_maxOutputPortCount = 1;
  m_minInputPortCount = 2;
  m_minOutputPortCount = 1;

  QPainterPath path;
  path.addRoundedRect(0, 0, WIDTH, HEIGHT, ROUND_RADIUS, ROUND_RADIUS);
  setPath(path);

  addInputPort(new Port(Input, 1, this, false, false));
  addInputPort(new Port(Input, 2, this, false, false));
  addOutputPort(new Port(Output, 3, this, false, false));
}

FlipFlopNode::~FlipFlopNode() {
}

AbstractNode* FlipFlopNode::create(const QString& id) {
  FlipFlopNode* node = new FlipFlopNode();
  node->m_id = id;
  return node;
}

bool FlipFlopNode::execute(QList<bool> args) {
  return args.at(0) & args.at(1);
}
