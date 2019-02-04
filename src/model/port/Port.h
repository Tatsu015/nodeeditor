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
    Port(IO io, uint64_t number, QGraphicsItem *parent = nullptr);
    virtual ~Port();

    QPointF centerScenePos();
    void addConnection(Connection* connection);
    void removeConnection(Connection* connection);

    QList<Connection*> connections() const;

    IO io() const;

    uint64_t number() const;

private:
    QList<Connection*> m_connections;
    IO m_io;
    uint64_t m_number = 0;
};

#endif // PORT_H
