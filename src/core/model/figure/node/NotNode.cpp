#include "NotNode.h"
#include "Define.h"
#include "FigureNamePublisher.h"
#include "PortFactory.h"
#include <QBrush>
#include <QFont>
#include <QPen>

NotNode::NotNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_NOT;
  m_io = Hidden;

  QPainterPath path;
  path.lineTo(QPointF(0, HEIGHT));
  path.lineTo(QPointF(WIDTH, HEIGHT * 0.5));
  path.closeSubpath();
  setPath(path);

  Port* port1 = PortFactory::getInstance()->createPort("port", Input, 1, this);
  port1->setPos(-port1->boundingRect().width() + PORT_POS_X_OFS,
                boundingRect().center().y() - port1->boundingRect().height() * 0.5);
  addPort(port1);

  Port* port2 = PortFactory::getInstance()->createPort("port", Output, 2, this, true);
  port2->setPos(boundingRect().width() - PORT_POS_X_OFS,
                boundingRect().center().y() - port2->boundingRect().height() * 0.5);
  addPort(port2);
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
