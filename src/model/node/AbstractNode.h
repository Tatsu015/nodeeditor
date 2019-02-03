#ifndef NODE_H
#define NODE_H

#include <QGraphicsPathItem>
#include "Common.h"

class Port;
class QGraphicsSimpleTextItem;

class AbstractNode : public QGraphicsPathItem
{
public:
    AbstractNode(QGraphicsItem *parent = nullptr);
    virtual ~AbstractNode();

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    virtual AbstractNode* create() = 0;

    QString name() const;
    void setName(const QString &name);

    void setupNameText();


    QList<Port*> ports() const;
    void addPort(Port* port);

    QList<AbstractNode*> adjastOutNodes();
    QList<AbstractNode*> adjastInNodes();
    QList<AbstractNode*> adjastNodes();

    EPosition portPosition(Port* port);

    QString nodeType() const;

protected:
    const static uint32_t NODE_SIZE      = 50;
    const static uint32_t PEN_SIZE       = 3;
    const static uint32_t ROUND_RADIUS   = 3;
    const static uint32_t PORT_POS_X_OFS = 2;
    const static uint32_t PORT_POS_Y_OFS = 5;

    QGraphicsSimpleTextItem* m_typeText = nullptr;
    QString m_activeType;

protected:
    QString m_nodeType;

private:
    QList<Port*> m_ports;
    QString m_name;
    QGraphicsSimpleTextItem* m_nameText = nullptr;
};

#endif // NODE_H
