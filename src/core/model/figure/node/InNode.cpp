#include "InNode.h"
#include "Common.h"
#include "Define.h"
#include "NamePublisher.h"
#include "PortFactory.h"
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QPen>

InNode::InNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_IN;
  m_io = Input;

  QPainterPath path;
  path.addRoundedRect(0, 0, WIDTH, HEIGHT * 0.5, ROUND_RADIUS, ROUND_RADIUS);
  setPath(path);

  Port* port1 = PortFactory::getInstance()->createPort("port", Output, 1, this);
  port1->setPos(boundingRect().width() - PORT_POS_X_OFS,
                boundingRect().center().y() - port1->boundingRect().height() * 0.5);
  addPort(port1);
}

InNode::~InNode() {
}

AbstractNode* InNode::create() {
  return new InNode();
}

bool InNode::execute(QList<bool> args) {
  return args.at(0);
}
