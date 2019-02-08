#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <QList>

class QMenu;

class MenuManager {
 public:
  static MenuManager* getInstance();
  void addMenu(QMenu* menu);
  QMenu* menu(const QString& name);
  QList<QMenu*> menus() const;

 private:
  QList<QMenu*> m_menus;

 private:
  MenuManager();
  ~MenuManager();
};
#endif  // MENUMANAGER_H
