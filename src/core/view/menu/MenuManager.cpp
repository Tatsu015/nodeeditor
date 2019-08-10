#include "MenuManager.h"
#include <QMenu>

const QString MenuManager::MENU_FILE = "File";
const QString MenuManager::MENU_EDIT = "Edit";
const QString MenuManager::MENU_VIEW = "View";

MenuManager* MenuManager::getInstance() {
  static MenuManager s;
  return &s;
}

void MenuManager::addMenu(QMenu* menu) {
  m_menus << menu;
}

QMenu* MenuManager::menu(const QString& name) {
  foreach (QMenu* menu, m_menus) {
    if (name == menu->title()) {
      return menu;
    }
  }
  return nullptr;
}

QList<QMenu*> MenuManager::menus() const {
  return m_menus;
}

void MenuManager::addContextMenuAction(QAction* action) {
  m_contectMenuActions << action;
}

QList<QAction*> MenuManager::contextMenuActions() const {
  return m_contectMenuActions;
}

MenuManager::MenuManager() {
}

MenuManager::~MenuManager() {
}
