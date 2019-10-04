#include "InvertPortPlugin.h"
#include "AbstractNode.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Port.h"
#include "Project.h"
#include "Scene.h"
#include <QInputDialog>
#include <QMenu>

InvertPortPlugin::InvertPortPlugin(QObject* parent) : AbstractPlugin(parent) {
  m_isContextMenuUse = true;
}

InvertPortPlugin::~InvertPortPlugin() {
}

QList<QAction*> InvertPortPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Q_UNUSED(event);
  return QList<QAction*>({m_action});
}

void InvertPortPlugin::doInit() {
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
