#ifndef HiddenNode_H
#define HiddenNode_H

#include "AbstractNode.h"

const static QString HIDDEN = "Hidden";

class HiddenNode : public AbstractNode
{
public:
    HiddenNode(QGraphicsItem *parent = nullptr);
    virtual ~HiddenNode();

    virtual AbstractNode* create();
};

#endif // HiddenNode_H
