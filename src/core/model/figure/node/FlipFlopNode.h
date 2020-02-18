#ifndef FLIPFLOPNODE_H
#define FLIPFLOPNODE_H

#include "AbstractNode.h"

class FlipFlopNode : public AbstractNode {
public:
  FlipFlopNode(QGraphicsItem* parent = nullptr);
  virtual ~FlipFlopNode();

  virtual AbstractNode* create(const QString& id);

  virtual bool execute(QList<bool> args);
};

#endif // FLIPFLOPNODE_H
