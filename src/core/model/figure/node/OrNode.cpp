#include "OrNode.h"
#include "Define.h"
#include "Port.h"
#include <QBrush>
#include <QFont>
#include <QPen>

OrNode::OrNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_OR;
  m_io = Hidden;
  m_maxInputPortCount = 4;
  m_maxOutputPortCount = 1;
  m_minInputPortCount = 2;
  m_minOutputPortCount = 1;

  QPainterPath path;
  path.cubicTo(QPointF(WIDTH * 0.1, HEIGHT * 0.2), QPointF(WIDTH * 0.1, HEIGHT * 0.8), QPointF(0, HEIGHT));
  path.lineTo(WIDTH * 0.3, HEIGHT);
  path.cubicTo(QPointF(WIDTH * 0.7, HEIGHT * 0.95), QPointF(WIDTH * 0.85, HEIGHT * 0.8), QPointF(WIDTH, HEIGHT * 0.5));
  path.cubicTo(QPointF(WIDTH * 0.85, HEIGHT * 0.2), QPointF(WIDTH * 0.7, HEIGHT * 0.05), QPointF(WIDTH * 0.3, 0));
  path.closeSubpath();
  setPath(path);

  addInputPort(new Port(Input, 1, this, false, false));
  addInputPort(new Port(Input, 2, this, false, false));
  addOutputPort(new Port(Output, 3, this, false, false));
}

OrNode::~OrNode() {
}

AbstractNode* OrNode::create(const QString& id) {
  OrNode* node = new OrNode();
  node->m_id = id;
  return node;
}

bool OrNode::execute(QList<bool> args) {
  return args.at(0) & args.at(1);
}
