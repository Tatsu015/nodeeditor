#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QList>

class AbstractPlugin;
class MainWindow;
namespace Ui {
class MainWindow;
}

class PluginLoader {
 public:
  static PluginLoader* getInstance();

  void init();
  void load(MainWindow* mainWindow, Ui::MainWindow* ui);

 private:
  void addPlugin(AbstractPlugin* plugin);

 private:
  QList<AbstractPlugin*> m_plugins;

 private:
  PluginLoader();
  ~PluginLoader();
};

#endif  // PLUGINLOADER_H
