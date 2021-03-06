#include "VertexRemovePlugin.h"
#include "AbstractConnection.h"
#include "Editor.h"
#include "MenuManager.h"
#include "NodeRemoveCommand.h"
#include "Project.h"
#include "Scene.h"
#include "VertexHandle.h"
#include "VertexRemoveCommand.h"
#include <QGraphicsSceneContextMenuEvent>

VertexRemovePlugin::VertexRemovePlugin(QObject* parent) : AbstractPlugin(parent) {
}

VertexRemovePlugin::~VertexRemovePlugin() {
}

QList<QAction*> VertexRemovePlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  m_deleteVertexHandleCache = scene->findVertexHandle(event->scenePos());
  if (!m_deleteVertexHandleCache) {
    return QList<QAction*>();
  }
  // keep connection selected when context menu appear
  m_deleteVertexHandleCache->connection()->setSelected(true);
  return QList<QAction*>({m_action});
}

void VertexRemovePlugin::doInit() {
  useContextMenu(true);

  m_action = new QAction("Delete Vertex");
  connect(m_action, &QAction::triggered, this, &VertexRemovePlugin::onExecute);
}

void VertexRemovePlugin::onExecute() {
  Scene* scene = Editor::getInstance()->project()->scene();
  Sheet* activeSheet = scene->sheet();
  Editor::getInstance()->addCommand(new VertexRemoveCommand(scene, activeSheet, m_deleteVertexHandleCache));
}
