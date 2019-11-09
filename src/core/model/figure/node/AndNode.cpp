#include "AndNode.h"
#include "Define.h"
#include "Port.h"
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QUuid>

AndNode::AndNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_AND;
  m_io = Hidden;
  m_maxInputPortCount = 4;
  m_maxOutputPortCount = 1;
  m_minInputPortCount = 2;
  m_minOutputPortCount = 1;

  QPainterPath path;
  path.lineTo(0, HEIGHT);
  path.lineTo(WIDTH * 0.5, HEIGHT);
  path.arcTo(0, 0, WIDTH, HEIGHT, 270, 180);
  path.closeSubpath();
  setPath(path);

  addInputPort(new Port(Input, 1, this, false, false));
  addInputPort(new Port(Input, 2, this, false, false));
  addOutputPort(new Port(Output, 3, this, false, false));
}

AndNode::~AndNode() {
}

AbstractNode* AndNode::create(const QString& id) {
  AndNode* node = new AndNode();
  node->m_id = id;
  return node;
}

bool AndNode::execute(QList<bool> args) {
  return args.at(0) & args.at(1);
}
