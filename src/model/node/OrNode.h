#ifndef OrNode_H
#define OrNode_H

#include "AbstractNode.h"

class OrNode : public AbstractNode {
 public:
  OrNode(QGraphicsItem* parent = nullptr);
  virtual ~OrNode();

  virtual AbstractNode* create();
};

#endif  // OrNode_H
