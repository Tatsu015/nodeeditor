#include "HiddenNode.h"
#include "Port.h"
#include <QPen>
#include <QBrush>
#include <QFont>

HiddenNode::HiddenNode(QGraphicsItem* parent):
    Node(parent),
    m_types(QStringList({"&", "|", "1", }))
{
    m_activeType = m_types.first();

    const static QBrush  BLUSH      = QBrush(QColor("#2aa52a"));
    const static QPen    PEN        = QPen(QColor("#008000"),PEN_SIZE);
    const static QColor  TEXT_COLOR = QColor("#008000");
    setBrush(BLUSH);
    setPen(PEN);

    QPainterPath path;
    path.addRoundedRect(0,0,NODE_SIZE, NODE_SIZE, ROUND_RADIUS, ROUND_RADIUS);
    setPath(path);

    Port* port1 = new Port(Input, this);
    port1->setPen(PEN);
    port1->setBrush(BLUSH);
    port1->setPos(-port1->boundingRect().width() + PORT_POS_X_OFS,
                  PORT_POS_Y_OFS);
    addPort(port1);

    Port* port2 = new Port(Input, this);
    port2->setPen(PEN);
    port2->setBrush(BLUSH);
    port2->setPos(-port2->boundingRect().width() + PORT_POS_X_OFS,
                  boundingRect().height() - port2->boundingRect().height() - PORT_POS_Y_OFS);
    addPort(port2);

    Port* port3 = new Port(Output, this);
    port3->setPen(PEN);
    port3->setBrush(BLUSH);
    port3->setPos(boundingRect().width() - PORT_POS_X_OFS,
                  boundingRect().center().y() - port3->boundingRect().height()*0.5);
    addPort(port3);

    m_typeText = new QGraphicsSimpleTextItem(m_activeType, this);
    QFont f;
    f.setPointSize(24);
    m_typeText->setPen(QPen(TEXT_COLOR));
    m_typeText->setBrush(QBrush(TEXT_COLOR));
    m_typeText->setFont(f);
    m_typeText->setPos(boundingRect().center() - m_typeText->boundingRect().center());
}

HiddenNode::~HiddenNode()
{
}

void HiddenNode::changeType()
{
    int nextIndex = m_types.indexOf(m_activeType) + 1;
    int kind  = m_types.count();

    m_activeType = m_types[nextIndex % kind];
    m_typeText->setText(m_activeType);
    m_typeText->setPos(boundingRect().center() - m_typeText->boundingRect().center());
}
