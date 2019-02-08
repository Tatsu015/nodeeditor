#include "OpenPlugin.h"
#include <QMenu>
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"

OpenPlugin::OpenPlugin() {}

OpenPlugin::~OpenPlugin() {}

void OpenPlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu("File");

  QAction* openAction = new QAction("Open");
  fileMenu->addAction(openAction);

  connect(openAction, &QAction::triggered, this, &OpenPlugin::onExecute);
}

void OpenPlugin::onExecute() {
  Editor::getInstance()->reset();
  Editor::getInstance()->project()->open("test.json");
}
