#ifndef InNode_H
#define InNode_H

#include "AbstractNode.h"

class QGraphicsSimpleTextItem;

class InNode : public AbstractNode {
public:
  InNode(QGraphicsItem* parent = nullptr);
  virtual ~InNode();

  virtual AbstractNode* create();

  virtual bool execute(QList<bool> args);
};

#endif // InNode_H
