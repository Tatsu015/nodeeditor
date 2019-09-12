#include "AbstractTool.h"

AbstractTool::AbstractTool(const QString& name) : m_name(name) {
}

AbstractTool::~AbstractTool() {
}

void AbstractTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void AbstractTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void AbstractTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void AbstractTool::mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void AbstractTool::keyPressEvent(Scene* scene, QKeyEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void AbstractTool::keyReleaseEvent(Scene* scene, QKeyEvent* event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

QString AbstractTool::name() const {
  return m_name;
}

bool AbstractTool::isUsing() const {
  return m_isUsing;
}

bool AbstractTool::isSelectable() const {
  return m_isNodeSelectable;
}
