#include "RemovePortPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Port.h"
#include "PortFactory.h"
#include "PortRemoveCommand.h"
#include "Project.h"
#include "Scene.h"
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QInputDialog>

RemovePortPlugin::RemovePortPlugin(QObject* parent) : AbstractPlugin(parent) {
}

RemovePortPlugin::~RemovePortPlugin() {
}

QList<QAction*> RemovePortPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> nodes = scene->findNodes(event->scenePos());
  if (0 >= nodes.count()) {
    return QList<QAction*>();
  }

  AbstractNode* node = nodes.first();
  if (node->canRemoveInputPort()) {
    return QList<QAction*>({m_action});
  }
  return QList<QAction*>();
}

void RemovePortPlugin::doInit() {
  useContextMenu(true);

  m_action = new QAction("Remove Port");
  connect(m_action, &QAction::triggered, this, &RemovePortPlugin::onExecute);
}

void RemovePortPlugin::onExecute() {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> nodes = scene->selectedNodes();
  if (1 != nodes.count()) {
    return;
  }

  QInputDialog selectPortDialog;
  QStringList portNames;
  AbstractNode* targetNode = nodes.first();
  foreach (Port* port, targetNode->ports()) {
    if (port->isRemovable()) {
      portNames << QString::number(port->number());
    }
  }
  uint32_t targetPortNum = selectPortDialog.getItem(nullptr, "Select Invert Port", "a", portNames).toUInt();
  Port* targetPort = targetNode->port(targetPortNum);

  Editor::getInstance()->addCommand(new PortRemoveCommand(scene, scene->sheet(), targetNode, targetPort));
}
