#include "CutPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "NodeRemoveCommand.h"
#include "Project.h"
#include "Scene.h"
#include <QMenu>

CutPlugin::CutPlugin(QObject* parent) : AbstractPlugin(parent) {
}

CutPlugin::~CutPlugin() {
}

void CutPlugin::doInit() {
  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_EDIT);

  QAction* action = new QAction("Cut");
  menu->addAction(action);
  MenuManager::getInstance()->addContextMenuAction(action);

  connect(action, &QAction::triggered, this, &CutPlugin::onExecute);
}

void CutPlugin::onExecute() {
  Scene* scene = Editor::getInstance()->project()->scene();
  Sheet* activeSheet = scene->sheet();
  Editor::getInstance()->addCommand(new NodeRemoveCommand(scene, activeSheet, scene->selectedNodes()));
}
