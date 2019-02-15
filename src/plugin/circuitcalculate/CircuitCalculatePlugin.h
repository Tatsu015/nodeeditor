#ifndef CircuitCalculatePLUGIN_H
#define CircuitCalculatePLUGIN_H

#include "AbstractPlugin.h"

class AbstractNode;
class IOTableWidget;

class CircuitCalculatePlugin : public AbstractPlugin {

private:
    struct ConnectedGraph {
      QString m_name;
      uint64_t m_id;
      QString m_description;
      QList<AbstractNode*> m_nodes;
    };

 public:
  CircuitCalculatePlugin();
  virtual ~CircuitCalculatePlugin();

 protected:
  virtual void initView(MainWindow* mainWindow, Ui::MainWindow* ui);
  void doInit();

private:
  bool CheckError(const QList<AbstractNode*>& nodes);
  bool CheckAllPortFilled(const QList<AbstractNode*>& nodes);
  QList<ConnectedGraph*> ConnectedGraphs(const QList<AbstractNode*>& nodes);
  QList<AbstractNode*> ExecuteOrderSort(ConnectedGraph* connectedGraph);

  bool isAllAdjacentInNodeVisited(AbstractNode* checkNode, const QList<AbstractNode*>& visitedNodes);

 private slots:
  void onRun();
  void onDebug();

private:
  IOTableWidget* m_ioTableWidget = nullptr;
};

#endif  // CircuitCalculatePLUGIN_H
