#include "AddPortPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Port.h"
#include "PortAddCommand.h"
#include "PortFactory.h"
#include "Project.h"
#include "Scene.h"
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>

AddPortPlugin::AddPortPlugin(QObject* parent) : AbstractPlugin(parent) {
  m_isContextMenuUse = true;
}

AddPortPlugin::~AddPortPlugin() {
}

QList<QAction*> AddPortPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> nodes = scene->findNodes(event->scenePos());
  if (0 >= nodes.count()) {
    return QList<QAction*>();
  }

  AbstractNode* node = nodes.first();
  if (node->canAddInputPort()) {
    return QList<QAction*>({m_action});
  }
  return QList<QAction*>();
}

void AddPortPlugin::doInit() {
  m_action = new QAction("Add Port");
  connect(m_action, &QAction::triggered, this, &AddPortPlugin::onExecute);
}

void AddPortPlugin::onExecute() {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> nodes = scene->selectedNodes();
  if (1 != nodes.count()) {
    return;
  }

  AbstractNode* targetNode = nodes.first();
  Port* port = PortFactory::getInstance()->createPort("port", Input, targetNode);
  Editor::getInstance()->addCommand(new PortAddCommand(scene, scene->sheet(), targetNode, port));
}
