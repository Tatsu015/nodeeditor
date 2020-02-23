#ifndef SHOWNODEINFOPLUGIN_H
#define SHOWNODEINFOPLUGIN_H

#include "AbstractPlugin.h"

class ShowNodeInfoPlugin : public AbstractPlugin {
public:
  ShowNodeInfoPlugin(QObject* parent = nullptr);
  virtual ~ShowNodeInfoPlugin();

protected:
  void doInit();

private slots:
  void onExecuteShowNodeName();
  void onExecuteShowNodeId();

private:
  QMenu* m_menu = nullptr;
  QAction* m_showNodeNameAction = nullptr;
  QAction* m_showNodeIdAction = nullptr;
};

#endif // SHOWNODEINFOPLUGIN_H
