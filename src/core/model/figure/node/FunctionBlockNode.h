#ifndef FunctionBlockNode_H
#define FunctionBlockNode_H

#include "AbstractNode.h"

class Sheet;

class FunctionBlockNode : public AbstractNode {
public:
  FunctionBlockNode(Sheet* sheet, QGraphicsItem* parent = nullptr);
  virtual ~FunctionBlockNode();

  virtual AbstractNode* create(const QString& id);

  virtual bool execute(QList<bool> args);

private:
  virtual void doSetup();

private:
  Sheet* m_sheet = nullptr;
};

#endif // FunctionBlockNode_H
