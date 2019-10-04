#include "ContextMenuManager.h"
#include "AbstractPlugin.h"
#include <QMenu>

ContextMenuManager* ContextMenuManager::getInstance() {
  static ContextMenuManager s;
  return &s;
}

void ContextMenuManager::addPlugin(AbstractPlugin* plugin) {
  m_plugins << plugin;
}

QList<QAction*> ContextMenuManager::actions(QGraphicsSceneContextMenuEvent* event) const {
  QList<QAction*> actions;
  foreach (AbstractPlugin* plugin, m_plugins) { actions.append(plugin->contextMenuActions(event)); }
  return actions;
}

ContextMenuManager::ContextMenuManager() {
}

ContextMenuManager::~ContextMenuManager() {
}
