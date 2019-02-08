#include "PluginLoader.h"
#include "AbstractPlugin.h"
#include "ui_MainWindow.h"

PluginLoader* PluginLoader::getInstance() {
  static PluginLoader s;
  return &s;
}

#include "NewPlugin.h"
#include "OpenPlugin.h"
#include "SavePlugin.h"
void PluginLoader::init() {
  // TODO this function will be dynamic lib plugin load
  addPlugin(new NewPlugin());
  addPlugin(new OpenPlugin());
  addPlugin(new SavePlugin());
}

void PluginLoader::load(Ui::MainWindow* ui) {
  foreach (AbstractPlugin* plugin, m_plugins) { plugin->init(ui); }
}

void PluginLoader::addPlugin(AbstractPlugin* plugin) { m_plugins << plugin; }

PluginLoader::PluginLoader() {}

PluginLoader::~PluginLoader() {}
