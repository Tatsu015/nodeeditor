#include "QuitPlugin.h"
#include "Editor.h"
#include "MenuManager.h"
#include <QApplication>
#include <QMenu>

QuitPlugin::QuitPlugin(QObject* parent) : AbstractPlugin(parent) {
}

QuitPlugin::~QuitPlugin() {
}

void QuitPlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu(MenuManager::MENU_FILE);

  QAction* quitAction = new QAction(QIcon("../resource/quit.png"), "Quit");
  quitAction->setShortcut(QKeySequence::Quit);
  fileMenu->addAction(quitAction);

  connect(quitAction, &QAction::triggered, this, &QuitPlugin::onExecute);
}

void QuitPlugin::onExecute() {
  qApp->exit();
}
