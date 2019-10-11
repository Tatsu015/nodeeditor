#include "InvertPortPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "InvertPortDialog.h"
#include "MenuManager.h"
#include "Port.h"
#include "Project.h"
#include "Scene.h"
#include <QGraphicsSceneContextMenuEvent>
#include <QInputDialog>
#include <QMenu>

InvertPortPlugin::InvertPortPlugin(QObject* parent) : AbstractPlugin(parent) {
}

InvertPortPlugin::~InvertPortPlugin() {
}

QList<QAction*> InvertPortPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> nodes = scene->findNodes(event->scenePos());
  if (0 >= nodes.count()) {
    return QList<QAction*>();
  }

  return QList<QAction*>({m_action});
}

void InvertPortPlugin::doInit() {
  useContextMenu(true);

  m_action = new QAction("Invert Port");
  connect(m_action, &QAction::triggered, this, &InvertPortPlugin::onExecute);
}

void InvertPortPlugin::onExecute() {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  QList<AbstractNode*> nodes = scene->selectedNodes();
  if (1 != nodes.count()) {
    return;
  }

  AbstractNode* targetNode = nodes.first();
  InvertPortDialog dialog;
  dialog.setupDialog(targetNode);
  int answer = dialog.exec();
  if (answer) {
    QList<Port*> invertPorts = dialog.invertPorts();
    foreach (Port* port, targetNode->ports()) {
      if (invertPorts.contains(port)) {
        port->invert(true);
      } else {
        port->invert(false);
      }
    }
  }
}
