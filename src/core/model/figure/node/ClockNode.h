#ifndef CLOCKNODE_H
#define CLOCKNODE_H

#include "AbstractNode.h"

class QGraphicsSimpleTextItem;

class ClockNode : public AbstractNode {
public:
  ClockNode(QGraphicsItem* parent = nullptr);
  virtual ~ClockNode();

  virtual AbstractNode* create(const QString& id);

  virtual bool execute(QList<bool> args);
};

#endif // CLOCKNODE_H
