#ifndef CIRCUITCALCULATEEXECUTOR_H
#define CIRCUITCALCULATEEXECUTOR_H

#include <QList>

class AbstractNode;

class CircuitCalculateExecutor {
 public:
  static CircuitCalculateExecutor* getInstance();

  void run();
  void next();
  void stepOver();
  void setupStack(QList<AbstractNode*> nodes);
  void teardownStack();
  int32_t stackCount() const;

 private:
  QList<bool> arguments(AbstractNode* node);

 private:
  QList<AbstractNode*> m_executeNodeStack;
  QList<AbstractNode*> m_breakPointNodes;

 private:
  CircuitCalculateExecutor();
  ~CircuitCalculateExecutor();
};

#endif  // CIRCUITCALCULATEEXECUTOR_H
