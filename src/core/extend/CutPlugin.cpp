#include "CutPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "NodeRemoveCommand.h"
#include "Project.h"
#include "Scene.h"
#include <QMenu>

CutPlugin::CutPlugin(QObject* parent) : AbstractPlugin(parent) {
  m_isContextMenuUse = true;
}

CutPlugin::~CutPlugin() {
}

QList<QAction*> CutPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Q_UNUSED(event);
  return QList<QAction*>({m_action});
}

void CutPlugin::doInit() {
  QMenu* menu = MenuManager::getInstance()->menu(MenuManager::MENU_EDIT);

  m_action = new QAction("Cut");
  menu->addAction(m_action);

  connect(m_action, &QAction::triggered, this, &CutPlugin::onExecute);
}

void CutPlugin::onExecute() {
  Scene* scene = Editor::getInstance()->project()->scene();
  Sheet* activeSheet = scene->sheet();
  Editor::getInstance()->addCommand(new NodeRemoveCommand(scene, activeSheet, scene->selectedNodes()));
}
