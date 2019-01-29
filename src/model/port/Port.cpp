#include "Port.h"
#include  "Connection.h"
#include <QBrush>
#include <QPen>

const static uint32_t PORT_SIZE = 12;

Port::Port(IO io, QGraphicsItem* parent):
    QGraphicsPathItem(parent),
    m_io(io)
{
    QPainterPath path;
    path.addEllipse(0,0,PORT_SIZE, PORT_SIZE);
    setPath(path);
}

Port::~Port()
{
}

QPointF Port::centerScenePos()
{
    return sceneBoundingRect().center();
}

void Port::addConnection(Connection* connection)
{
    m_connections << connection;
}

void Port::removeConnection(Connection* connection)
{
    m_connections.removeOne(connection);
}

QList<Connection*> Port::connections() const
{
    return m_connections;
}

IO Port::io() const
{
    return m_io;
}

