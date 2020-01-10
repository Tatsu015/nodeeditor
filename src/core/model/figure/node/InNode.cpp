#include "InNode.h"
#include "Common.h"
#include "Define.h"
#include "Port.h"
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QPen>

const static QString NODE_IN = "In";

InNode::InNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_IN;
  m_io = Input;
  m_maxInputPortCount = 0;
  m_maxOutputPortCount = 1;
  m_minInputPortCount = 0;
  m_minOutputPortCount = 1;

  QPainterPath path;
  path.addRoundedRect(0, 0, WIDTH, HEIGHT * 0.5, ROUND_RADIUS, ROUND_RADIUS);
  setPath(path);

  addOutputPort(new Port(Output, 1, this, false, false));
}

InNode::~InNode() {
}

AbstractNode* InNode::create(const QString& id) {
  InNode* node = new InNode();
  node->m_id = id;
  return node;
}

bool InNode::execute(QList<bool> args) {
  return args.at(0);
}
