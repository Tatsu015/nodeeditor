#ifndef ADDPORTPLUGIN_H
#define ADDPORTPLUGIN_H

#include "AbstractPlugin.h"

class AddPortPlugin : public AbstractPlugin {
public:
  AddPortPlugin(QObject* parent = nullptr);
  virtual ~AddPortPlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
};

#endif // ADDPORTPLUGIN_H
