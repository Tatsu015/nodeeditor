#ifndef PORT_H
#define PORT_H

#include <QGraphicsPathItem>

class Connection;
class Port;
class AbstractNode;

enum IO : uint32_t{
    Input,
    Output,
};

class Port : public QGraphicsPathItem
{
public:
    Port(IO io, uint32_t number, QGraphicsItem *parent = nullptr);
    virtual ~Port();

    QPointF centerScenePos();
    void addConnection(Connection* connection);
    void removeConnection(Connection* connection);

    QList<Connection*> connections() const;

    IO io() const;

    uint32_t number() const;

    AbstractNode *parentNode() const;

private:
    QList<Connection*> m_connections;
    AbstractNode*      m_parentNode = nullptr;
    IO m_io;
    uint32_t m_number;
};

#endif // PORT_H
