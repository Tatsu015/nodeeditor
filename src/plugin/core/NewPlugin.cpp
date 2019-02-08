#include "NewPlugin.h"
#include <QMenu>
#include "Editor.h"
#include "MenuManager.h"

NewPlugin::NewPlugin() {}

NewPlugin::~NewPlugin() {}

void NewPlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu("File");

  QAction* newAction = new QAction("New");
  fileMenu->addAction(newAction);

  connect(newAction, &QAction::triggered, this, &NewPlugin::onExecute);
}

void NewPlugin::onExecute() { Editor::getInstance()->reset(); }
