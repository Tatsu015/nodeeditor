#ifndef NODE_H
#define NODE_H

#include <QGraphicsPathItem>
#include "Common.h"

class Port;
class QGraphicsSimpleTextItem;

class Node : public QGraphicsPathItem
{
public:
    Node(QGraphicsItem *parent = nullptr);
    virtual ~Node();

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QString Name() const;

    void addPort(Port* port);
    QList<Port*> ports() const;

    QList<Node*> adjastOutNodes();
    QList<Node*> adjastInNodes();
    QList<Node*> adjastNodes();

    virtual void changeType() = 0;

    EPosition portPosition(Port* port);

protected:
    const static uint32_t NODE_SIZE      = 50;
    const static uint32_t PEN_SIZE       = 3;
    const static uint32_t ROUND_RADIUS   = 3;
    const static uint32_t PORT_POS_X_OFS = 2;
    const static uint32_t PORT_POS_Y_OFS = 5;

    QGraphicsSimpleTextItem* m_typeText = nullptr;
    QString m_activeType;

private:
    QList<Port*> m_ports;
    QString m_name;
    QGraphicsSimpleTextItem* m_nameText = nullptr;
};

#endif // NODE_H
