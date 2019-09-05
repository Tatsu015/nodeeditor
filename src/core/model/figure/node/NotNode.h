#ifndef NotNode_H
#define NotNode_H

#include "AbstractNode.h"

class NotNode : public AbstractNode {
public:
  NotNode(QGraphicsItem* parent = nullptr);
  virtual ~NotNode();

  virtual AbstractNode* create(const QString& id);

  virtual bool execute(QList<bool> args);
};

#endif // NotNode_H
