#include "Connection.h"
#include "Port.h"
#include "Connector.h"
#include <QPen>

Connection::Connection(QGraphicsItem* parent):
    QGraphicsPathItem(parent)
{
    setPen(QPen(Qt::gray, 2));
}

Connection::~Connection()
{
}

void Connection::setStartPos(const QPointF& startPos)
{
    m_startPos = startPos;
    updatePath();
}

void Connection::setEndPos(const QPointF& endPos)
{
    m_endPos = endPos;
    updatePath();
}

void Connection::setStartPort(Port* startPort)
{
    m_startPort = startPort;
    updatePath();
}

void Connection::setEndPort(Port* endPort)
{
    m_endPort = endPort;
    updatePath();
}

#include <QDebug>
void Connection::updatePath()
{
    QPointF startPos = m_startPos;
    QPointF endPos   = m_endPos;
    if(m_startPort){
        startPos = m_startPort->centerScenePos();
    }
    if(m_endPort){
        endPos   = m_endPort->centerScenePos();
    }

    QPointF elbowPos = (startPos + endPos)*0.5;

    QPainterPath path;
    QPointF elbow1(elbowPos.x(), startPos.y());
    QPointF elbow2(elbowPos.x(), endPos.y());
    path.moveTo(startPos);
    path.lineTo(elbow1);
    path.lineTo(elbow2);
    path.lineTo(endPos);
    path.lineTo(elbow2);
    path.lineTo(elbow1);
    path.closeSubpath();
    setPath(path);
}

Port* Connection::startPort() const
{
    return m_startPort;
}

Port* Connection::endPort() const
{
    return m_endPort;
}

Port*Connection::oppositeSidePort(Port* port)
{
    if(port == m_startPort){
        return m_endPort;
    }
    else{
        return m_startPort;
    }
}

void Connection::addConnector(Connector* connector)
{
    connector->setParentItem(this);
    m_connectors << connector;
}
