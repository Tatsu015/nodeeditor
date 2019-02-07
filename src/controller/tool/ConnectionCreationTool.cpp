#include "ConnectionCreationTool.h"
#include <QGraphicsSceneMouseEvent>
#include "Connection.h"
#include "ConnectionFactory.h"
#include "Define.h"
#include "Editor.h"
#include "Port.h"
#include "Scene.h"

ConnectionCreationTool::ConnectionCreationTool() {}

ConnectionCreationTool::~ConnectionCreationTool() {}

void ConnectionCreationTool::mousePressEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  m_startPort = scene->findPort(event->scenePos());
  if (!m_startPort) {
    return;
  }

  m_tmpConnection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
  addTmpConnection(scene, m_startPort);

  m_isUsing = true;
}

void ConnectionCreationTool::mouseMoveEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(scene);
  if (!m_startPort) {
    return;
  }

  redrawTmpConnection(event->scenePos());
}

void ConnectionCreationTool::mouseReleaseEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
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

void ConnectionCreationTool::mouseDoubleClickEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void ConnectionCreationTool::addTmpConnection(Scene *scene, Port *startPort) { scene->addConnection(m_tmpConnection, startPort); }

void ConnectionCreationTool::redrawTmpConnection(QPointF nowScenePos) { m_tmpConnection->updatePath(m_startPort, nowScenePos); }

void ConnectionCreationTool::decideConnection(Port *endPort) {
  m_tmpConnection->setEndPort(endPort);
  m_tmpConnection->setEndPos(endPort->centerScenePos());
  endPort->addConnection(m_tmpConnection);

  m_tmpConnection->updatePath();

  m_tmpConnection = nullptr;
  m_startPort = nullptr;
}

void ConnectionCreationTool::removeTmpConnection(Scene *scene) { scene->removeConnection(m_tmpConnection); }
