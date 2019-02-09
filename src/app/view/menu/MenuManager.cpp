#include "MenuManager.h"
#include <QMenu>

MenuManager* MenuManager::getInstance() {
  static MenuManager s;
  return &s;
}

void MenuManager::addMenu(QMenu* menu) { m_menus << menu; }

QMenu* MenuManager::menu(const QString& name) {
  foreach (QMenu* menu, m_menus) {
    if (name == menu->title()) {
      return menu;
    }
  }
  return nullptr;
}

QList<QMenu*> MenuManager::menus() const { return m_menus; }

MenuManager::MenuManager() {
  addMenu(new QMenu("File"));
  addMenu(new QMenu("Edit"));
}

MenuManager::~MenuManager() {}
