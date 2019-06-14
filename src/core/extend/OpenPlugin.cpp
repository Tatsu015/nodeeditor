#include "OpenPlugin.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"
#include <QMenu>

OpenPlugin::OpenPlugin(QObject* parent) : AbstractPlugin(parent) {
}

OpenPlugin::~OpenPlugin() {
}

void OpenPlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* openAction = new QAction(QIcon("../resource/open.png"), "Open");
  openAction->setShortcut(QKeySequence::Open);
  fileMenu->addAction(openAction);

  connect(openAction, &QAction::triggered, this, &OpenPlugin::onExecute);
}

void OpenPlugin::onExecute() {
  Editor::getInstance()->reset();
  Project* project = Editor::getInstance()->project();
  QString fileName = project->filePath();
  project->open(fileName);
}
