#include "QuitPlugin.h"
#include <QApplication>
#include <QMenu>
#include "Editor.h"
#include "MenuManager.h"

QuitPlugin::QuitPlugin() {}

QuitPlugin::~QuitPlugin() {}

void QuitPlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu("File");

  QAction* quitAction = new QAction("Quit");
  quitAction->setShortcut(QKeySequence::Quit);
  fileMenu->addAction(quitAction);

  connect(quitAction, &QAction::triggered, this, &QuitPlugin::onExecute);
}

void QuitPlugin::onExecute() { qApp->exit(); }
