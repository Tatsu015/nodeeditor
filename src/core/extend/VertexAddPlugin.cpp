#include "VertexAddPlugin.h"
#include "AbstractConnection.h"
#include "Editor.h"
#include "MenuManager.h"
#include "Project.h"
#include "Scene.h"
#include "VertexAddCommand.h"
#include "VertexHandle.h"
#include <QGraphicsSceneContextMenuEvent>

VertexAddPlugin::VertexAddPlugin(QObject* parent) : AbstractPlugin(parent) {
}

VertexAddPlugin::~VertexAddPlugin() {
}

QList<QAction*> VertexAddPlugin::contextMenuActions(QGraphicsSceneContextMenuEvent* event) const {
  Project* project = Editor::getInstance()->project();
  Scene* scene = project->scene();
  m_pos = event->scenePos();
  m_connectionleCache = scene->findConnection(event->scenePos(), nullptr);
  if (!m_connectionleCache) {
    return QList<QAction*>();
  }
  // keep connection selected when context menu appear
  m_connectionleCache->setSelected(true);
  return QList<QAction*>({m_action});
}

void VertexAddPlugin::doInit() {
  useContextMenu(true);

  m_action = new QAction("Add Vertex");
  connect(m_action, &QAction::triggered, this, &VertexAddPlugin::onExecute);
}

void VertexAddPlugin::onExecute() {
  Scene* scene = Editor::getInstance()->project()->scene();
  Sheet* activeSheet = scene->sheet();

  int32_t areaIndex = m_connectionleCache->areaIndex(m_pos);
  VertexHandle* vertexHandle = new VertexHandle();
  vertexHandle->setPos(m_pos);
  Editor::getInstance()->addCommand(
      new VertexAddCommand(scene, activeSheet, vertexHandle, m_connectionleCache, areaIndex));
}
