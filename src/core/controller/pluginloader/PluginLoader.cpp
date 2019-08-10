#include "PluginLoader.h"
#include "AbstractPlugin.h"
#include "CircuitCalculatePlugin.h"
#include "MainWindow.h"
#include "NewPlugin.h"
#include "OpenPlugin.h"
#include "QuitPlugin.h"
#include "SavePlugin.h"
#include "ShowNodeNamePlugin.h"
#include "ui_MainWindow.h"

PluginLoader* PluginLoader::getInstance() {
  static PluginLoader s;
  return &s;
}

void PluginLoader::init() {
  // TODO this function will be dynamic lib plugin load
  addPlugin(new NewPlugin());
  addPlugin(new OpenPlugin());
  addPlugin(new SavePlugin());
  addPlugin(new QuitPlugin());
  addPlugin(new CircuitCalculatePlugin());
  addPlugin(new ShowNameViewPlugin());
}

void PluginLoader::load(MainWindow* mainWindow, Ui::MainWindow* ui) {
  foreach (AbstractPlugin* plugin, m_plugins) { plugin->init(mainWindow, ui); }
}

void PluginLoader::reset() {
  foreach (AbstractPlugin* plugin, m_plugins) { plugin->reset(); }
}

void PluginLoader::addPlugin(AbstractPlugin* plugin) {
  m_plugins << plugin;
}

PluginLoader::PluginLoader() {
}

PluginLoader::~PluginLoader() {
}
