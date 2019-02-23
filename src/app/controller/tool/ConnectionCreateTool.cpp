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
#include "Connector.h"

ConnectionCreateTool::ConnectionCreateTool() : AbstractTool(TOOL_CONNECTION_CREATE) {
  m_tmpConnection = new TmpConnection();
  m_tmpConnector = new Connector();
}

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

  bool connectable = canConnect(scene, event);
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
  if (!canConnect(scene, event)) {
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

void ConnectionCreateTool::addTmpConnector(Scene* scene, Port* startPort)
{

}

void ConnectionCreateTool::redrawTmpConnector(QPointF nowScenePos)
{

}

void ConnectionCreateTool::decideConnector(Scene* scene, Port* endPort)
{

}

void ConnectionCreateTool::removeTmpConnector(Scene* scene)
{

}

bool ConnectionCreateTool::canConnect(Scene* scene, QGraphicsSceneMouseEvent* event) const
{
  Port *endPort = scene->findPort(event->scenePos());

  if (!endPort) {
    return false;
  }
  if (m_startPort == endPort) {
    return false;
  }
  if (m_startPort->parentNode() == endPort->parentNode()) {
    return false;
  }
  if (m_startPort->io() == endPort->io()) {
    return false;
  }
  return true;
}
