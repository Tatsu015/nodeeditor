#include "SavePlugin.h"
#include <QMenu>
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"

SavePlugin::SavePlugin() {}

SavePlugin::~SavePlugin() {}

void SavePlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu("File");

  QAction* saveAction = new QAction("Save");
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
