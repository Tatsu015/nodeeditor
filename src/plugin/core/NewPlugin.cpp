#include "NewPlugin.h"
#include <QMenu>
#include "Editor.h"
#include "MenuManager.h"

NewPlugin::NewPlugin(QObject* parent) : AbstractPlugin(parent) {}

NewPlugin::~NewPlugin() {}

void NewPlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* newAction = new QAction(QIcon("../resource/new.png"), "New");
  newAction->setShortcut(QKeySequence::New);
  fileMenu->addAction(newAction);

  connect(newAction, &QAction::triggered, this, &NewPlugin::onExecute);
}

void NewPlugin::onExecute() { Editor::getInstance()->reset(); }
