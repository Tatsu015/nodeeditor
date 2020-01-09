#ifndef INVERTPORTPLUGIN_H
#define INVERTPORTPLUGIN_H

#include "AbstractPlugin.h"

class InvertPortPlugin : public AbstractPlugin {
public:
  InvertPortPlugin(QObject* parent = nullptr);
  virtual ~InvertPortPlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
};

#endif // INVERTPORTPLUGIN_H
