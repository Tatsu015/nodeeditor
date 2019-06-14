#ifndef HiddenNode_H
#define HiddenNode_H

#include "AbstractNode.h"

class AndNode : public AbstractNode {
public:
  AndNode(QGraphicsItem* parent = nullptr);
  virtual ~AndNode();

  virtual AbstractNode* create();

  virtual bool execute(QList<bool> args);
};

#endif // HiddenNode_H
