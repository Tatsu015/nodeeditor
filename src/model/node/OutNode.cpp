#include "OutNode.h"
#include <QBrush>
#include <QPen>
#include "Define.h"
#include "NamePublisher.h"
#include "Port.h"

OutNode::OutNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_OUT;

  QPainterPath path;
  path.addRoundedRect(0, 0, WIDTH, HEIGHT * 0.5, ROUND_RADIUS, ROUND_RADIUS);
  setPath(path);

  Port* port1 = new Port(Input, 1, this);
  port1->setPos(-port1->boundingRect().width() + PORT_POS_X_OFS, boundingRect().center().y() - port1->boundingRect().height() * 0.5);
  addPort(port1);
}

OutNode::~OutNode() {}

AbstractNode* OutNode::create() { return new OutNode(); }
