#include "ClockNode.h"
#include "Common.h"
#include "Define.h"
#include "Port.h"
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QPen>

const static QString NODE_CLOCK = CLOCK;

ClockNode::ClockNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_CLOCK;
  m_io = Input;
  m_maxInputPortCount = 0;
  m_maxOutputPortCount = 1;
  m_minInputPortCount = 0;
  m_minOutputPortCount = 1;

  QPainterPath path;
  path.addEllipse(0, 0, 0.5 * WIDTH, 0.5 * HEIGHT);
  setPath(path);

  addOutputPort(new Port(Output, 1, this, false, false));
}

ClockNode::~ClockNode() {
}

AbstractNode* ClockNode::create(const QString& id) {
  ClockNode* node = new ClockNode();
  node->m_id = id;
  return node;
}

bool ClockNode::execute(QList<bool> args) {
  return args.at(0);
}
