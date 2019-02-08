#ifndef OutNode_H
#define OutNode_H

#include "AbstractNode.h"

class OutNode : public AbstractNode {
 public:
  OutNode(QGraphicsItem* parent = nullptr);
  virtual ~OutNode();

  virtual AbstractNode* create();
};

#endif  // OutNode_H
