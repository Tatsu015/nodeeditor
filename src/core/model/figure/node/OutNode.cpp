#include "OutNode.h"
#include "Define.h"
#include "FigureNamePublisher.h"
#include "Port.h"
#include <QBrush>
#include <QPen>

OutNode::OutNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_OUT;
  m_io = Output;
  m_maxInputPortCount = 1;
  m_maxOutputPortCount = 0;

  QPainterPath path;
  path.addRoundedRect(0, 0, WIDTH, HEIGHT * 0.5, ROUND_RADIUS, ROUND_RADIUS);
  setPath(path);

  addInputPort(new Port(Input, 1, this));
}

OutNode::~OutNode() {
}

AbstractNode* OutNode::create(const QString& id) {
  OutNode* node = new OutNode();
  node->m_id = id;
  return node;
}

bool OutNode::execute(QList<bool> args) {
  return args.at(0);
}
