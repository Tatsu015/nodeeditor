#include "NewPlugin.h"
#include "Editor.h"
#include "MenuManager.h"
#include <QMenu>

NewPlugin::NewPlugin(QObject* parent) : AbstractPlugin(parent) {
}

NewPlugin::~NewPlugin() {
}

void NewPlugin::doInit() {
  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* newAction = new QAction(QIcon("../resource/new.png"), "New");
  newAction->setShortcut(QKeySequence::New);
  menu->addAction(newAction);

  connect(newAction, &QAction::triggered, this, &NewPlugin::onExecute);
}

void NewPlugin::onExecute() {
  Editor::getInstance()->reset();
}
