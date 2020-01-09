#ifndef ORNODE_H
#define ORNODE_H

#include "AbstractNode.h"

class OrNode : public AbstractNode {
public:
  OrNode(QGraphicsItem* parent = nullptr);
  virtual ~OrNode();

  virtual AbstractNode* create(const QString& id);

  virtual bool execute(QList<bool> args);
};

#endif // ORNODE_H
