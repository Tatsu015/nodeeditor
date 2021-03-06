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

  void init(MainWindow* mainWindow, Ui::MainWindow* ui);
  void reset();

private:
  void addPlugin(MainWindow* mainWindow, Ui::MainWindow* ui, AbstractPlugin* plugin);

private:
  QList<AbstractPlugin*> m_plugins;

private:
  PluginLoader();
  ~PluginLoader();
};

#endif // PLUGINLOADER_H
