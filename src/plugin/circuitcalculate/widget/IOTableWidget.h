#ifndef IOTABLEWIDGET_H
#define IOTABLEWIDGET_H

#include <QTableWidget>
#include "SceneObserver.h"

class IOTableWidget : public QTableWidget, public SceneObserver {
 public:
  IOTableWidget(QWidget* parent = nullptr);
  virtual ~IOTableWidget();

  virtual void addNode(AbstractNode* node);
  virtual void removeNode(AbstractNode* node);

  void read();
};

#endif  // IOTABLEWIDGET_H
