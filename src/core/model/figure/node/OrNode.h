#ifndef OrNode_H
#define OrNode_H

#include "AbstractNode.h"

class OrNode : public AbstractNode {
public:
  OrNode(QGraphicsItem* parent = nullptr);
  virtual ~OrNode();

  virtual AbstractNode* create();

  virtual bool execute(QList<bool> args);
};

#endif // OrNode_H
