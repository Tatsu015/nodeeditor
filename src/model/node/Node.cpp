#include "Node.h"
#include "Connection.h"
#include "Port.h"
#include <QBrush>
#include <QPen>
#include <QGraphicsSimpleTextItem>

Node::Node(QGraphicsItem* parent):
    QGraphicsPathItem(parent)
{
    static uint64_t num;
    m_name = "Node" + QString::number(num++);
    m_nameText = new QGraphicsSimpleTextItem(m_name, this);
    m_nameText->setPos(0,-20);
    m_nameText->setPen(QPen(Qt::white));
    m_nameText->setBrush(QBrush(Qt::white));

    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

Node::~Node()
{
}

QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
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

void Node::addPort(Port* port)
{
    m_ports << port;
}

QList<Node*> Node::adjastOutNodes()
{
    QList<Node*> nodes;
    foreach (Port* port, m_ports) {
        foreach (Connection* connection, port->connections()) {
            Node* outNode = dynamic_cast<Node*>(connection->endPort()->parentItem());
            if(outNode != this){
                nodes << outNode;
            }
        }
    }
    return nodes;
}

QList<Node*> Node::adjastInNodes()
{
    QList<Node*> nodes;
    foreach (Port* port, m_ports) {
        foreach (Connection* connection, port->connections()) {
            Node* inNode = dynamic_cast<Node*>(connection->startPort()->parentItem());
            if(inNode != this){
                nodes << inNode;
            }
        }
    }
    return nodes;
}

QList<Node*> Node::adjastNodes()
{
    QList<Node*> nodes;
    foreach (Port* port, m_ports) {
        foreach (Connection* connection, port->connections()) {
            Node* inNode = dynamic_cast<Node*>(connection->startPort()->parentItem());
            if(inNode != this){
                // when exist loop, this check need
                if(!nodes.contains(inNode)){
                    nodes << inNode;
                }
            }
            Node* outNode = dynamic_cast<Node*>(connection->endPort()->parentItem());
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

EPosition Node::portPosition(Port* port)
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

QList<Port*> Node::ports() const
{
    return m_ports;
}

QString Node::Name() const
{
    return m_name;
}
