#include "InNode.h"
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include "Common.h"
#include "Define.h"
#include "NamePublisher.h"
#include "Port.h"

InNode::InNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_IN;

  m_activeType = "true";

  QPainterPath path;
  path.addRoundedRect(0, 0, WIDTH, HEIGHT * 0.5, ROUND_RADIUS, ROUND_RADIUS);
  setPath(path);

  Port* port1 = new Port(Output, 1, this);
  port1->setPos(boundingRect().width() - PORT_POS_X_OFS, boundingRect().center().y() - port1->boundingRect().height() * 0.5);
  addPort(port1);

  m_typeText = new QGraphicsSimpleTextItem(m_activeType, this);
  m_typeText->setPen(QPen(TEXT_COLOR));
  m_typeText->setBrush(QBrush(TEXT_COLOR));
  m_typeText->setPos(boundingRect().center() - m_typeText->boundingRect().center());
}

InNode::~InNode() {}

AbstractNode* InNode::create() { return new InNode(); }
