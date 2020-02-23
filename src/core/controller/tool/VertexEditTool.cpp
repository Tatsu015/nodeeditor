#include "VertexEditTool.h"
#include "AbstractConnection.h"
#include "Define.h"
#include "Editor.h"
#include "Scene.h"
#include "VertexHandle.h"
#include "VertexMoveCommand.h"
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>

VertexEditTool::VertexEditTool() : AbstractTool(TOOL_VERTEX_EDIT) {
}

VertexEditTool::~VertexEditTool() {
}

void VertexEditTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (Qt::LeftButton != event->button()) {
    return;
  }
  m_editingVertexHandle = scene->findVertexHandle(event->scenePos());
  if (m_editingVertexHandle) {
    m_editingVertexHandle->connection()->startEditVertex();
    m_editingVertexHandle->setFlag(QGraphicsItem::ItemIsSelectable, true);
    m_editingVertexHandle->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_isUsing = true;
  }
}

void VertexEditTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);

  if (m_editingVertexHandle) {
    m_editingVertexHandle->connection()->redraw();
  }
}

void VertexEditTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  if (m_editingVertexHandle) {
    QPointF startScenePos = event->buttonDownScenePos(Qt::LeftButton);
    QPointF endScenePos = event->scenePos();
    QPointF diffScenePos = endScenePos - startScenePos;

    Editor::getInstance()->addCommand(
        new VertexMoveCommand(scene, scene->sheet(), m_editingVertexHandle, diffScenePos));

    m_editingVertexHandle->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_editingVertexHandle->setFlag(QGraphicsItem::ItemIsMovable, false);
    m_editingVertexHandle->connection()->endEditVertex();
    m_editingVertexHandle = nullptr;
  }
  m_isUsing = false;
}

bool VertexEditTool::isActivatable(Scene* scene, QGraphicsSceneMouseEvent* event) {
  VertexHandle* vertexHandle = scene->findVertexHandle(event->scenePos(), false);
  if (vertexHandle) {
    QGuiApplication::setOverrideCursor(QCursor(Qt::OpenHandCursor));
    return true;
  }
  return false;
}
