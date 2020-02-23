#include "CircuitCalculateExecutor.h"
#include "AbstractNode.h"
#include "DataBase.h"
#include <QBrush>

CircuitCalculateExecutor* CircuitCalculateExecutor::getInstance() {
  static CircuitCalculateExecutor s;
  return &s;
}

void CircuitCalculateExecutor::run() {
  while (m_executeNodeStack.count()) {
    stepOver();
  }
}

void CircuitCalculateExecutor::next() {
  while (m_executeNodeStack.count()) {
    AbstractNode* node = m_executeNodeStack.takeFirst();
    node->setBrush(QBrush(Qt::red));
    QList<bool> args = arguments(node);
    bool result = node->execute(args);
    node->setToolTip(btos(result));
    DataBase::getInstance()->write(node->name(), result);

    if (m_breakPointNodes.contains(node)) {
      return;
    }
  }
}

void CircuitCalculateExecutor::stepOver() {
  AbstractNode* node = m_executeNodeStack.takeFirst();
  node->setBrush(QBrush(Qt::red));
  QList<bool> args = arguments(node);
  bool result = node->execute(args);
  node->setToolTip(btos(result));

  DataBase::getInstance()->write(node->name(), result);
}

void CircuitCalculateExecutor::setupStack(QList<AbstractNode*> nodes) {
  m_executeNodeStack.append(nodes);
}

void CircuitCalculateExecutor::teardownStack() {
  m_executeNodeStack.clear();
}

int32_t CircuitCalculateExecutor::stackCount() const {
  return m_executeNodeStack.count();
}

QList<bool> CircuitCalculateExecutor::arguments(AbstractNode* node) {
  QList<bool> args;
  if (0 == node->adjastInNodes().count()) {
    args << DataBase::getInstance()->read(node->name());
  } else {
    foreach (AbstractNode* inNode, node->adjastInNodes()) { args << DataBase::getInstance()->read(inNode->name()); }
  }
  return args;
}

CircuitCalculateExecutor::CircuitCalculateExecutor() {
}

CircuitCalculateExecutor::~CircuitCalculateExecutor() {
}
