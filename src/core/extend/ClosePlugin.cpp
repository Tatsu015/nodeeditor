#include "ClosePlugin.h"
#include "Editor.h"
#include "MenuManager.h"
#include "PluginLoader.h"
#include "Project.h"
#include <QMenu>

ClosePlugin::ClosePlugin(QObject* parent) : AbstractPlugin(parent) {
}

ClosePlugin::~ClosePlugin() {
}

void ClosePlugin::doInit() {
  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* newAction = new QAction(QIcon("../resource/close.png"), "Close");
  newAction->setShortcut(QKeySequence::Close);
  menu->addAction(newAction);

  connect(newAction, &QAction::triggered, this, &ClosePlugin::onExecute);
}

void ClosePlugin::onExecute() {
  Project* oldProject = Editor::getInstance()->project();
  Project* newProject = new Project();

  newProject->takeOver(oldProject);
  delete oldProject;
  Editor::getInstance()->changeProject(newProject);
  Editor::getInstance()->run();
  PluginLoader::getInstance()->reset();
}
