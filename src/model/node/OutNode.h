#ifndef OutNode_H
#define OutNode_H

#include "Node.h"

const static QString OUT = "Out";

class OutNode : public Node
{
public:
    OutNode(QGraphicsItem *parent = nullptr);
    virtual ~OutNode();

    virtual void changeType();
};

#endif // OutNode_H
