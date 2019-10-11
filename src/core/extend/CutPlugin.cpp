#include "CutPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "NodeRemoveCommand.h"
#include "Project.h"
#include "Scene.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>

CutPlugin::CutPlugin(QObject* parent) : AbstractPlugin(parent) {
}

CutPlugin::~CutPlugin() {
}

QList<QAction*> CutPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> nodes = scene->findNodes(event->scenePos());
  if (0 >= nodes.count()) {
    return QList<QAction*>();
  }

  return QList<QAction*>({m_action});
}

void CutPlugin::doInit() {
  useContextMenu(true);

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
