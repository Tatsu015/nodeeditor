#ifndef CIRCUITCALCULATEPLUGIN_H
#define CIRCUITCALCULATEPLUGIN_H

#include "AbstractPlugin.h"

class AbstractNode;
class IOTableWidget;
class DebugControlWidget;
class QDockWidget;

class CircuitCalculatePlugin : public AbstractPlugin {
  Q_OBJECT

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

signals:
  void startDebug(const QString& text, int timeout = 0);

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
  void tearDown();

private slots:
  void onCompile();
  void onRun();
  void onStartDebug();
  void onStopDebug();

  void onStepOver();
  void onNext();

private:
  DebugControlWidget* m_DebugControlWidget = nullptr;
  QList<ConnectedGraph*> m_connectedGraphs;
  QDockWidget* m_ioSetDockWidget = nullptr;
};

#endif // CIRCUITCALCULATEPLUGIN_H
