#include "SavePlugin.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"
#include <QMenu>

SavePlugin::SavePlugin(QObject* parent) : AbstractPlugin(parent) {
}

SavePlugin::~SavePlugin() {
}

void SavePlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* saveAction = new QAction(QIcon("../resource/save.png"), "Save");
  saveAction->setShortcut(QKeySequence::Save);
  fileMenu->addAction(saveAction);

  connect(saveAction, &QAction::triggered, this, &SavePlugin::onExecute);
}

void SavePlugin::onExecute() {
  Project* project = Editor::getInstance()->project();
  QString fileName = project->filePath();
  project->save(fileName);
  Editor::getInstance()->projectNameChanged(project->fileBaseName());
}
