#include "PluginLoader.h"
#include "AbstractPlugin.h"
#include "AddPortPlugin.h"
#include "AlignPlugin.h"
#include "CircuitCalculatePlugin.h"
#include "ContextMenuManager.h"
#include "CutPlugin.h"
#include "InvertPortPlugin.h"
#include "MainWindow.h"
#include "NewPlugin.h"
#include "OpenPlugin.h"
#include "QuitPlugin.h"
#include "RemovePortPlugin.h"
#include "SavePlugin.h"
#include "ShowNodeNamePlugin.h"
#include "ui_MainWindow.h"

PluginLoader* PluginLoader::getInstance() {
  static PluginLoader s;
  return &s;
}

void PluginLoader::init(MainWindow* mainWindow, Ui::MainWindow* ui) {
  // TODO this function will be dynamic lib plugin load
  addPlugin(mainWindow, ui, new NewPlugin());
  addPlugin(mainWindow, ui, new OpenPlugin());
  addPlugin(mainWindow, ui, new SavePlugin());
  addPlugin(mainWindow, ui, new QuitPlugin());
  addPlugin(mainWindow, ui, new CircuitCalculatePlugin());
  addPlugin(mainWindow, ui, new ShowNameViewPlugin());
  addPlugin(mainWindow, ui, new CutPlugin());
  addPlugin(mainWindow, ui, new AlignPlugin());
  addPlugin(mainWindow, ui, new InvertPortPlugin());
  addPlugin(mainWindow, ui, new AddPortPlugin());
  addPlugin(mainWindow, ui, new RemovePortPlugin());
}

void PluginLoader::reset() {
  foreach (AbstractPlugin* plugin, m_plugins) { plugin->reset(); }
}

void PluginLoader::addPlugin(MainWindow* mainWindow, Ui::MainWindow* ui, AbstractPlugin* plugin) {
  plugin->init(mainWindow, ui);
  m_plugins << plugin;
  if (plugin->isContextMenuUse()) {
    ContextMenuManager::getInstance()->addPlugin(plugin);
  }
}

PluginLoader::PluginLoader() {
}

PluginLoader::~PluginLoader() {
}
