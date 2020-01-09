#ifndef REMOVEPORTPLUGIN_H
#define REMOVEPORTPLUGIN_H

#include "AbstractPlugin.h"

class RemovePortPlugin : public AbstractPlugin {
public:
  RemovePortPlugin(QObject* parent = nullptr);
  virtual ~RemovePortPlugin();

  virtual QList<QAction*> contextMenuActions(QGraphicsSceneContextMenuEvent* event) const;

protected:
  void doInit();

private slots:
  void onExecute();

private:
  QAction* m_action = nullptr;
};

#endif // REMOVEPORTPLUGIN_H
