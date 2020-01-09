#ifndef OUTNODE_H
#define OUTNODE_H

#include "AbstractNode.h"

class OutNode : public AbstractNode {
public:
  OutNode(QGraphicsItem* parent = nullptr);
  virtual ~OutNode();

  virtual AbstractNode* create(const QString& id);

  virtual bool execute(QList<bool> args);
};

#endif // OUTNODE_H
