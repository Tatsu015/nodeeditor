#include "NotNode.h"
#include "Define.h"
#include "FigureNamePublisher.h"
#include "Port.h"
#include <QBrush>
#include <QFont>
#include <QPen>

NotNode::NotNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_NOT;
  m_io = Hidden;
  m_maxInputPortCount = 1;
  m_maxOutputPortCount = 1;

  QPainterPath path;
  path.lineTo(QPointF(0, HEIGHT));
  path.lineTo(QPointF(WIDTH, HEIGHT * 0.5));
  path.closeSubpath();
  setPath(path);

  addInputPort(new Port(Input, 1, this));
  addOutputPort(new Port(Output, 2, this, true));
}

NotNode::~NotNode() {
}

AbstractNode* NotNode::create(const QString& id) {
  NotNode* node = new NotNode();
  node->m_id = id;
  return node;
}

bool NotNode::execute(QList<bool> args) {
  return !args.at(0);
}
