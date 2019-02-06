#include "ConnectionCreationTool.h"
#include <QGraphicsSceneMouseEvent>
#include "Scene.h"
#include "Port.h"
#include "ConnectionFactory.h"
#include "Define.h"
#include "Connection.h"

ConnectionCreationTool::ConnectionCreationTool()
{

}

ConnectionCreationTool::~ConnectionCreationTool()
{

}

void ConnectionCreationTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent *event)
{
    m_startPort = scene->findPort(event->scenePos());
    if(!m_startPort){
        return;
    }

    m_tmpConnection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
    m_isUsing = true;
}

void ConnectionCreationTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent *event)
{
    if(!m_startPort){
        return;
    }

    redrawTmpConnection(scene, m_startPort, event->scenePos());
}

void ConnectionCreationTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent *event)
{
    if(!m_startPort){
        return;
    }

    Port* endPort = scene->findPort(event->scenePos());
    if(!endPort){
        removeTmpConnection();
    }
    if(m_startPort == endPort){
        removeTmpConnection();
    }
    if(m_startPort->parentNode() == endPort->parentNode()){
        removeTmpConnection();
    }

    decideConnection();

    m_isUsing = false;
}

void ConnectionCreationTool::mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(scene);
    Q_UNUSED(event);
}

void ConnectionCreationTool::redrawTmpConnection(Scene* scene, Port *startPort, QPointF nowScenePos)
{
    m_tmpConnection->updatePath(startPort, nowScenePos);
}

void ConnectionCreationTool::decideConnection()
{

}

void ConnectionCreationTool::removeTmpConnection()
{

}
