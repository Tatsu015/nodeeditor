#ifndef InNode_H
#define InNode_H

#include "AbstractNode.h"

class QGraphicsSimpleTextItem;

class InNode : public AbstractNode {
 public:
  InNode(QGraphicsItem* parent = nullptr);
  virtual ~InNode();

  virtual AbstractNode* create();

 private:
  QGraphicsSimpleTextItem* m_typeText = nullptr;
};

#endif  // InNode_H
