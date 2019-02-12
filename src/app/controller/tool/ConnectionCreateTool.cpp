#include "ConnectionCreateTool.h"
#include <QGraphicsSceneMouseEvent>
#include "AbstractNode.h"
#include "Connection.h"
#include "ConnectionAddCommand.h"
#include "ConnectionFactory.h"
#include "Define.h"
#include "Editor.h"
#include "NodeRemoveCommand.h"
#include "Port.h"
#include "Scene.h"
#include "TmpConnection.h"

ConnectionCreateTool::ConnectionCreateTool() : AbstractTool(TOOL_CONNECTION_CREATE) { m_tmpConnection = new TmpConnection(); }

ConnectionCreateTool::~ConnectionCreateTool() {}

void ConnectionCreateTool::mousePressEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  m_startPort = scene->findPort(event->scenePos());
  if (!m_startPort) {
    return;
  }

  addTmpConnection(scene, m_startPort);

  m_isUsing = true;
  m_isNodeSelectable = false;
}

void ConnectionCreateTool::mouseMoveEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(scene);
  if (!m_startPort) {
    return;
  }

  Port *endPort = scene->findPort(event->scenePos());
  bool connectable = canConnect(m_startPort, endPort);
  m_tmpConnection->changePenStyle(connectable);

  redrawTmpConnection(event->scenePos());
}

void ConnectionCreateTool::mouseReleaseEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  if (!m_startPort) {
    return;
  }

  m_isUsing = false;
  m_isNodeSelectable = true;

  Port *endPort = scene->findPort(event->scenePos());
  removeTmpConnection(scene);
  if (!canConnect(m_startPort, endPort)) {
    return;
  }

  decideConnection(scene, endPort);
}

void ConnectionCreateTool::mouseDoubleClickEvent(Scene *scene, QGraphicsSceneMouseEvent *event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void ConnectionCreateTool::keyPressEvent(Scene *scene, QKeyEvent *event) {
  if (Qt::Key_Delete == event->key()) {
    Editor::getInstance()->addCommand(new NodeRemoveCommand(scene, scene->selectedNodes()));
  }
}

void ConnectionCreateTool::keyReleaseEvent(Scene *scene, QKeyEvent *event) {
  Q_UNUSED(scene);
  Q_UNUSED(event);
}

void ConnectionCreateTool::addTmpConnection(Scene *scene, Port *startPort) { scene->addConnection(m_tmpConnection, startPort); }

void ConnectionCreateTool::redrawTmpConnection(QPointF nowScenePos) { m_tmpConnection->redraw(m_startPort, nowScenePos); }

void ConnectionCreateTool::decideConnection(Scene *scene, Port *endPort) {
  Connection *connection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
  ConnectionAddCommand *command = new ConnectionAddCommand(scene, connection, m_startPort, endPort);
  Editor::getInstance()->addCommand(command);

  m_startPort = nullptr;
}

void ConnectionCreateTool::removeTmpConnection(Scene *scene) { scene->removeConnection(m_tmpConnection); }

bool ConnectionCreateTool::canConnect(Port *startPort, Port *endPort) const {
  if (!endPort) {
    return false;
  }
  if (startPort == endPort) {
    return false;
  }
  if (startPort->parentNode() == endPort->parentNode()) {
    return false;
  }
  if (startPort->io() == endPort->io()) {
    return false;
  }
  return true;
}
