#include "InvertPortPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
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
  QInputDialog selectPortDialog;
  selectPortDialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
  QStringList portNames;
  AbstractNode* targetNode = nodes.first();
  foreach (Port* port, targetNode->ports()) { portNames << QString::number(port->number()); }
  uint32_t targetPortNum = selectPortDialog.getItem(nullptr, "Select Invert Port", "a", portNames).toUInt();
  Port* targetPort = targetNode->port(targetPortNum);

  targetPort->invert(!targetPort->isInvert());
}
