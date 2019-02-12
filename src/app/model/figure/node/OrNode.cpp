#include "OrNode.h"
#include <QBrush>
#include <QFont>
#include <QPen>
#include "Define.h"
#include "NamePublisher.h"
#include "Port.h"

OrNode::OrNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_OR;

  QPainterPath path;
  path.cubicTo(QPointF(WIDTH * 0.1, HEIGHT * 0.2), QPointF(WIDTH * 0.1, HEIGHT * 0.8), QPointF(0, HEIGHT));
  path.lineTo(WIDTH * 0.3, HEIGHT);
  path.cubicTo(QPointF(WIDTH * 0.7, HEIGHT * 0.95), QPointF(WIDTH * 0.85, HEIGHT * 0.8), QPointF(WIDTH, HEIGHT * 0.5));
  path.cubicTo(QPointF(WIDTH * 0.85, HEIGHT * 0.2), QPointF(WIDTH * 0.7, HEIGHT * 0.05), QPointF(WIDTH * 0.3, 0));
  path.closeSubpath();
  setPath(path);

  Port* port1 = new Port(Input, 1, this);
  port1->setPos(-port1->boundingRect().width() + PORT_POS_X_OFS, PORT_POS_Y_OFS);
  addPort(port1);

  Port* port2 = new Port(Input, 2, this);
  port2->setPos(-port2->boundingRect().width() + PORT_POS_X_OFS, boundingRect().height() - port2->boundingRect().height() - PORT_POS_Y_OFS);
  addPort(port2);

  Port* port3 = new Port(Output, 3, this);
  port3->setPos(boundingRect().width() - PORT_POS_X_OFS, boundingRect().center().y() - port3->boundingRect().height() * 0.5);
  addPort(port3);
}

OrNode::~OrNode() {}

AbstractNode* OrNode::create() { return new OrNode(); }