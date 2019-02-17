#ifndef CircuitCalculatePLUGIN_H
#define CircuitCalculatePLUGIN_H

#include "AbstractPlugin.h"

class AbstractNode;
class IOTableWidget;
class DebugControlDialog;

class CircuitCalculatePlugin : public AbstractPlugin {

private:
    struct ConnectedGraph {
      QString m_name;
      uint64_t m_id;
      QString m_description;
      QList<AbstractNode*> m_nodes;
    };

 public:
  CircuitCalculatePlugin(QObject* parent = nullptr);
  virtual ~CircuitCalculatePlugin();
  virtual void reset();

 protected:
  virtual void initView(MainWindow* mainWindow, Ui::MainWindow* ui);
  void doInit();

private:
  bool CheckError(const QList<AbstractNode*>& nodes);
  bool CheckAllPortFilled(const QList<AbstractNode*>& nodes);
  QList<ConnectedGraph*> ConnectedGraphs(const QList<AbstractNode*>& nodes);
  QList<AbstractNode*> ExecuteOrderSort(ConnectedGraph* connectedGraph);

  bool isAllAdjacentInNodeVisited(AbstractNode* checkNode, const QList<AbstractNode*>& visitedNodes);

private:
  void compile(QList<AbstractNode*>& nodes);
  void run(QList<AbstractNode*>& nodes);

  QList<bool> arguments(AbstractNode* node);

 private slots:
  void onCompile();
  void onRun();
  void onDebug();
  void onProgress();

private:
  IOTableWidget* m_ioTableWidget = nullptr;
  DebugControlDialog* m_debugControlDialog = nullptr;
  QList<ConnectedGraph*> m_connectedGraphs;
  QList<AbstractNode*> m_executeNodeStack;
};

#endif  // CircuitCalculatePLUGIN_H
