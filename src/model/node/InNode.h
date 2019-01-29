#ifndef InNode_H
#define InNode_H

#include "Node.h"

class QGraphicsSimpleTextItem;

const static QString IN = "In";

class InNode : public Node
{
public:
    InNode(QGraphicsItem *parent = nullptr);
    virtual ~InNode();

    virtual void changeType();

private:
    QGraphicsSimpleTextItem* m_typeText = nullptr;
};

#endif // InNode_H
