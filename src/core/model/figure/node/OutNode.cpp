#include "OutNode.h"
#include "Define.h"
#include "FigureNamePublisher.h"
#include "PortFactory.h"
#include <QBrush>
#include <QPen>

OutNode::OutNode(QGraphicsItem* parent) : AbstractNode(parent) {
  m_nodeType = NODE_OUT;
  m_io = Output;

  QPainterPath path;
  path.addRoundedRect(0, 0, WIDTH, HEIGHT * 0.5, ROUND_RADIUS, ROUND_RADIUS);
  setPath(path);

  Port* port1 = PortFactory::getInstance()->createPort("port", Input, 1, this);
  port1->setPos(-port1->boundingRect().width() + PORT_POS_X_OFS,
                boundingRect().center().y() - port1->boundingRect().height() * 0.5);
  addPort(port1);
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
