#ifndef CONNECTION_H
#define CONNECTION_H

#include <QGraphicsPathItem>

class Port;
class Connector;

class Connection : public QGraphicsPathItem
{
public:
    Connection(QGraphicsItem *parent = nullptr);
    virtual ~Connection();

    void setStartPos(const QPointF& startPos);
    void setEndPos(const QPointF& endPos);

    void setStartPort(Port* startPort);
    void setEndPort(Port* endPort);

    void updatePath();

    Port* startPort() const;
    Port* endPort() const;

    Port* oppositeSidePort(Port* port);
    void addConnector(Connector* connector);

private:
    QPointF m_startPos;
    QPointF m_endPos;
    Port*   m_startPort = nullptr;
    Port*   m_endPort   = nullptr;

    QList<Connector*> m_connectors;
};

#endif // CONNECTION_H
