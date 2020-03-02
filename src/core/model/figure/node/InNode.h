#ifndef INNODE_H
#define INNODE_H

#include "AbstractNode.h"

class QGraphicsSimpleTextItem;

class InNode : public AbstractNode {
public:
  InNode(QGraphicsItem* parent = nullptr);
  virtual ~InNode();

  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

  virtual AbstractNode* create(const QString& id);

  virtual bool execute(QList<bool> args);
};

#endif // INNODE_H
