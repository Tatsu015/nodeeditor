#ifndef NODETOOLBAR_H
#define NODETOOLBAR_H

#include "ProjectObserver.h"
#include <QToolBar>

class NodeEditTool;

class NodeToolBar : public QToolBar, public ProjectObserver {
  Q_OBJECT

public:
  NodeToolBar(QWidget* parent = nullptr);
  virtual ~NodeToolBar();

  void addToolBarAction(QAction* action);
  void removeToolBarAction(QAction* action);
  void setNodeEditTool(NodeEditTool* NodeEditTool);
  void changeDefaultTool();

  virtual void addSheet(Sheet* sheet);
  virtual void changeSheet(Sheet* sheet);
  virtual void removeSheet(Sheet* sheet);

private:
  void changeTool(QAction* activeAction);

private slots:
  void onChangeTool();

private:
  NodeEditTool* m_NodeEditTool = nullptr;
};

#endif // NODETOOLBAR_H
