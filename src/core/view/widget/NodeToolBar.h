#ifndef NODETOOLBAR_H
#define NODETOOLBAR_H

#include <QToolBar>

class FunctionBlockToolButton;
class NodeEditTool;

class NodeToolBar : public QToolBar {
  Q_OBJECT

public:
  NodeToolBar(QWidget* parent = nullptr);
  virtual ~NodeToolBar();

  void addToolBarAction(QAction* action);
  void addToolButton(FunctionBlockToolButton* toolButton);
  void removeToolBarAction(QAction* action);
  void setNodeEditTool(NodeEditTool* NodeEditTool);
  void changeDefaultTool();

private:
  void changeTool(QAction* activeAction);
  void changeTool(FunctionBlockToolButton* toolButton);

private slots:
  void onChangeTool();

private:
  NodeEditTool* m_NodeEditTool = nullptr;
  QMap<QString, QAction*> m_actions;
  FunctionBlockToolButton* m_functionBlockToolButton = nullptr;
};

#endif // NODETOOLBAR_H
