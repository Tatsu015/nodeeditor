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
};

#endif // NODETOOLBAR_H
