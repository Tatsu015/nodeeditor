#ifndef NODETOOLBAR_H
#define NODETOOLBAR_H

#include <QToolBar>

class NodeEditTool;

class NodeToolBar : public QToolBar {
  Q_OBJECT

public:
  NodeToolBar(QWidget* parent = nullptr);
  virtual ~NodeToolBar();

  void addToolBarAction(const QString& nodeType);
  void setNodeEditTool(NodeEditTool* NodeEditTool);
  void changeDefaultTool();

private:
  void changeTool(QAction* activeAction);

private slots:
  void onChangeTool();

private:
  NodeEditTool* m_NodeEditTool = nullptr;
};

#endif // NODETOOLBAR_H
