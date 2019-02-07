#include "ConnectionCreateTool.h"
#include <QGraphicsSceneMouseEvent>
#include "Connection.h"
#include "ConnectionFactory.h"
#include "Define.h"
#include "Editor.h"
#include "Port.h"
#include "Scene.h"

ConnectionCreateTool::ConnectionCreateTool() : AbstractTool(TOOL_CONNECTION_CREATE) {}

ConnectionCreateTool::~ConnectionCreateTool() {}

void ConnectionCreateTool::mousePressEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  m_startPort = scene->findPort(event->scenePos());
  if (!m_startPort) {
    return;
  }

  m_tmpConnection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
  addTmpConnection(scene, m_startPort);

  m_isUsing = true;
}

void ConnectionCreateTool::mouseMoveEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(scene);
  if (!m_startPort) {
    return;
  }

  redrawTmpConnection(event->scenePos());
}

void ConnectionCreateTool::mouseReleaseEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  if (!m_startPort) {
    return;
  }

  m_isUsing = false;

  Port *endPort = scene->findPort(event->scenePos());
  if (!endPort) {
    removeTmpConnection(scene);
    return;
  }
  if (m_startPort == endPort) {
    removeTmpConnection(scene);
    return;
  }
  if (m_startPort->parentNode() == endPort->parentNode()) {
    removeTmpConnection(scene);
    return;
  }

  decideConnection(endPort);
}

void ConnectionCreateTool::mouseDoubleClickEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void ConnectionCreateTool::addTmpConnection(Scene *scene, Port *startPort) { scene->addConnection(m_tmpConnection, startPort); }

void ConnectionCreateTool::redrawTmpConnection(QPointF nowScenePos) { m_tmpConnection->updatePath(m_startPort, nowScenePos); }

void ConnectionCreateTool::decideConnection(Port *endPort) {
  m_tmpConnection->setEndPort(endPort);
  m_tmpConnection->setEndPos(endPort->centerScenePos());
  endPort->addConnection(m_tmpConnection);

  m_tmpConnection->updatePath();

  m_tmpConnection = nullptr;
  m_startPort = nullptr;
}

void ConnectionCreateTool::removeTmpConnection(Scene *scene) { scene->removeConnection(m_tmpConnection); }
