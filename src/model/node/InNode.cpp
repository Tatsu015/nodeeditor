#include "InNode.h"
#include "Port.h"
#include "Common.h"
#include <QPen>
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include "NamePublisher.h"
#include "Define.h"

InNode::InNode(QGraphicsItem* parent):
    AbstractNode(parent)
{
    m_nodeType = NODE_IN;

    m_activeType = "true";

    const static QBrush  BLUSH      = QBrush(QColor("#a52a2a"));
    const static QPen    PEN        = QPen(QColor("#800000"),PEN_SIZE);
    const static QColor  TEXT_COLOR = QColor("#800000");
    setBrush(BLUSH);
    setPen(PEN);

    QPainterPath path;
    path.addRoundedRect(0,0,NODE_SIZE, NODE_SIZE*0.5, ROUND_RADIUS, ROUND_RADIUS);
    setPath(path);

    Port* port1 = new Port(Output, 1, this);
    port1->setPen(PEN);
    port1->setBrush(BLUSH);
    port1->setPos(boundingRect().width() - PORT_POS_X_OFS,
                  boundingRect().center().y() - port1->boundingRect().height()*0.5);
    addPort(port1);

    m_typeText = new QGraphicsSimpleTextItem(m_activeType, this);
    m_typeText->setPen(QPen(TEXT_COLOR));
    m_typeText->setBrush(QBrush(TEXT_COLOR));
    m_typeText->setPos(boundingRect().center() - m_typeText->boundingRect().center());
}

InNode::~InNode()
{
}

AbstractNode *InNode::create()
{
    return new InNode();
}
