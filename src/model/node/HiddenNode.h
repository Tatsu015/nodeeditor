#ifndef HiddenNode_H
#define HiddenNode_H

#include "Node.h"

const static QString HIDDEN = "Hidden";

class HiddenNode : public Node
{
public:
    HiddenNode(QGraphicsItem *parent = nullptr);
    virtual ~HiddenNode();

    virtual void changeType();

private:
    QStringList m_types;
};

#endif // HiddenNode_H
