#include "AbstractNode.h"
#include "Connection.h"
#include "Port.h"
#include <QBrush>
#include <QPen>
#include <QGraphicsSimpleTextItem>

AbstractNode::AbstractNode(QGraphicsItem* parent):
    QGraphicsPathItem(parent)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

AbstractNode::~AbstractNode()
{
}

QVariant AbstractNode::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if(ItemPositionChange == change){
        foreach (Port* port, m_ports) {
            foreach (Connection* connection, port->connections()) {
                connection->updatePath();
            }
        }
    }
    return QGraphicsPathItem::itemChange(change, value);
}

QString AbstractNode::name() const
{
    return m_name;
}

void AbstractNode::setName(const QString &name)
{
    m_name = name;
}

void AbstractNode::setupNameText()
{
    m_nameText = new QGraphicsSimpleTextItem(m_name, this);
    m_nameText->setPos(0,-20);
    m_nameText->setPen(QPen(Qt::white));
    m_nameText->setBrush(QBrush(Qt::white));
}

QList<Port*> AbstractNode::ports() const
{
    return m_ports;
}

void AbstractNode::addPort(Port* port)
{
    m_ports << port;
}

Port *AbstractNode::port(const uint64_t number)
{
    foreach (Port* port, m_ports) {
        if(number == port->number()){
            return port;
        }
    }
    return nullptr;
}

QList<AbstractNode*> AbstractNode::adjastOutNodes()
{
    QList<AbstractNode*> nodes;
    foreach (Port* port, m_ports) {
        foreach (Connection* connection, port->connections()) {
            AbstractNode* outNode = dynamic_cast<AbstractNode*>(connection->endPort()->parentItem());
            if(outNode != this){
                nodes << outNode;
            }
        }
    }
    return nodes;
}

QList<AbstractNode*> AbstractNode::adjastInNodes()
{
    QList<AbstractNode*> nodes;
    foreach (Port* port, m_ports) {
        foreach (Connection* connection, port->connections()) {
            AbstractNode* inNode = dynamic_cast<AbstractNode*>(connection->startPort()->parentItem());
            if(inNode != this){
                nodes << inNode;
            }
        }
    }
    return nodes;
}

QList<AbstractNode*> AbstractNode::adjastNodes()
{
    QList<AbstractNode*> nodes;
    foreach (Port* port, m_ports) {
        foreach (Connection* connection, port->connections()) {
            AbstractNode* inNode = dynamic_cast<AbstractNode*>(connection->startPort()->parentItem());
            if(inNode != this){
                // when exist loop, this check need
                if(!nodes.contains(inNode)){
                    nodes << inNode;
                }
            }
            AbstractNode* outNode = dynamic_cast<AbstractNode*>(connection->endPort()->parentItem());
            if(outNode != this){
                // when exist loop, this check need
                if(!nodes.contains(outNode)){
                    nodes << outNode;
                }
            }
        }
    }

    return nodes;
}

EPosition AbstractNode::portPosition(Port* port)
{
    QPointF center     = sceneBoundingRect().center();
    QPointF portCenter = port->sceneBoundingRect().center();

    QPointF centerDiffVector = portCenter - center;
    QPointF originDirVector  = QPointF(1, 0);

    QLineF diffLine(QPointF(0, 0),   centerDiffVector);
    QLineF originLine(QPointF(0, 0), originDirVector);

    qreal angle = diffLine.angleTo(originLine);

    if((45 <= angle) && (angle < 135)){
        return Bottom;
    }
    else if((135 <= angle) && (angle < 225)){
        return Left;
    }
    else if((225 <= angle) && (angle < 315)){
        return Top;
    }
    else{
        return Right;
    }
}

QString AbstractNode::nodeType() const
{
    return m_nodeType;
}
