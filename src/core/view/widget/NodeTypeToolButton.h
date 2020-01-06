#ifndef NODETYPETOOLBUTTON_H
#define NODETYPETOOLBUTTON_H

#include <QToolButton>

class NodeTypeToolButton : public QToolButton {
public:
  NodeTypeToolButton(QString& nodeName, QWidget* parent = nullptr);
  virtual ~NodeTypeToolButton();

private slots:
  void onChangeNodeType();
};

#endif // NODETYPETOOLBUTTON_H
