#include "ExitPlugin.h"
#include <QApplication>
#include <QMenu>
#include "Editor.h"
#include "MenuManager.h"

ExitPlugin::ExitPlugin() {}

ExitPlugin::~ExitPlugin() {}

void ExitPlugin::doInit() {
  QMenu* fileMenu = MenuManager::getInstance()->menu("File");

  QAction* exitAction = new QAction("Exit");
  fileMenu->addAction(exitAction);

  connect(exitAction, &QAction::triggered, this, &ExitPlugin::onExecute);
}

void ExitPlugin::onExecute() { qApp->exit(); }
