#include "AndNode.h"
#include <QBrush>
#include <QFont>
#include <QPen>
#include "Define.h"
#include "NamePublisher.h"
#include "PortFactory.h"

AndNode::AndNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_AND;
  m_io = Hidden;

  QPainterPath path;
  path.lineTo(0, HEIGHT);
  path.lineTo(WIDTH * 0.5, HEIGHT);
  path.arcTo(0, 0, WIDTH, HEIGHT, 270, 180);
  path.closeSubpath();
  setPath(path);

  Port* port1 = PortFactory::getInstance()->createPort("port", Input, 1, this);
  port1->setPos(-port1->boundingRect().width() + PORT_POS_X_OFS, PORT_POS_Y_OFS);
  addPort(port1);

  Port* port2 = PortFactory::getInstance()->createPort("port", Input, 2, this);
  port2->setPos(-port2->boundingRect().width() + PORT_POS_X_OFS, boundingRect().height() - port2->boundingRect().height() - PORT_POS_Y_OFS);
  addPort(port2);

  Port* port3 = PortFactory::getInstance()->createPort("port", Output, 3, this);
  port3->setPos(boundingRect().width() - PORT_POS_X_OFS, boundingRect().center().y() - port3->boundingRect().height() * 0.5);
  addPort(port3);
}

AndNode::~AndNode() {}

AbstractNode* AndNode::create() { return new AndNode(); }

bool AndNode::execute(QList<bool> args) { return args.at(0) & args.at(1); }
