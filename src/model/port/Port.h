#ifndef PORT_H
#define PORT_H

#include <QGraphicsPathItem>

class Connection;
class Port;

enum IO : uint32_t{
    Input,
    Output,
};

class Port : public QGraphicsPathItem
{
public:
    Port(IO io, QGraphicsItem *parent = nullptr);
    virtual ~Port();

    QPointF centerScenePos();
    void addConnection(Connection* connection);
    void removeConnection(Connection* connection);

    QList<Connection*> connections() const;

    IO io() const;

private:
    QList<Connection*> m_connections;
    IO m_io;
};

#endif // PORT_H
