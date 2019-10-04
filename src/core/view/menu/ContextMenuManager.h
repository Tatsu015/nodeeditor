#ifndef CONTEXTMENUMANAGER_H
#define CONTEXTMENUMANAGER_H

#include <QList>

class QMenu;
class QAction;
class QGraphicsSceneContextMenuEvent;
class AbstractPlugin;

class ContextMenuManager {

public:
  static ContextMenuManager* getInstance();
  void addPlugin(AbstractPlugin* plugin);
  QList<QAction*> actions(QGraphicsSceneContextMenuEvent* event) const;

private:
  QList<AbstractPlugin*> m_plugins;

private:
  ContextMenuManager();
  ~ContextMenuManager();
};
#endif // CONTEXTMENUMANAGER_H
