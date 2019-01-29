#include "OutNode.h"
#include "Port.h"
#include <QPen>
#include <QBrush>

OutNode::OutNode(QGraphicsItem* parent):
    Node(parent)
{
    const static QBrush BLUSH = QBrush(QColor("#2a2aa5"));
    const static QPen   PEN   = QPen(QColor("#000080"),PEN_SIZE);
    setBrush(BLUSH);
    setPen(PEN);

    QPainterPath path;
    path.addRoundedRect(0,0,NODE_SIZE, NODE_SIZE*0.5, ROUND_RADIUS, ROUND_RADIUS);
    setPath(path);

    Port* port1 = new Port(Input, this);
    port1->setPen(PEN);
    port1->setBrush(BLUSH);
    port1->setPos(-port1->boundingRect().width() + PORT_POS_X_OFS,
                  boundingRect().center().y() - port1->boundingRect().height()*0.5);
    addPort(port1);
}

OutNode::~OutNode()
{
}

void OutNode::changeType()
{
    // nop
}
