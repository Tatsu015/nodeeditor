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

QMenu* ContextMenuManager::contextMenu(QGraphicsSceneContextMenuEvent* event) const {
  m_menu->clear();
  foreach (AbstractPlugin* plugin, m_plugins) {
    QMenu* subMenu = plugin->contextSubMenu(event);
    if (subMenu) {
      m_menu->addMenu(plugin->contextSubMenu(event));
    }
    foreach (QAction* action, plugin->contextMenuActions(event)) { m_menu->addAction(action); }
  }
  return m_menu;
}

QList<QAction*> ContextMenuManager::actions(QGraphicsSceneContextMenuEvent* event) const {
  QList<QAction*> actions;
  foreach (AbstractPlugin* plugin, m_plugins) { actions.append(plugin->contextMenuActions(event)); }
  return actions;
}

ContextMenuManager::ContextMenuManager() : m_menu(new QMenu()) {
}

ContextMenuManager::~ContextMenuManager() {
}
