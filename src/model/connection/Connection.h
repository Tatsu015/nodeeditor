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

    Connection* create();

    void setStartPos(const QPointF& startPos);
    void setEndPos(const QPointF& endPos);

    void setStartPort(Port* startPort);
    void setEndPort(Port* endPort);

    void updatePath();
    void updatePath(Port* startPort, Port* endPort);
    void updatePath(Port* startPort, QPointF endScenePos);

    Port* startPort() const;
    Port* endPort() const;

    void removeStartPort();
    void removeEndPort();

    Port* oppositeSidePort(Port* port);
    void addConnector(Connector* connector);

    QString name() const;
    void setName(const QString &name);

    QString connectionType() const;

private:
    QString m_name      = "";
    QString m_connectionType = "";
    QPointF m_startPos;
    QPointF m_endPos;
    Port*   m_startPort = nullptr;
    Port*   m_endPort   = nullptr;

    QList<Connector*> m_connectors;
};

#endif // CONNECTION_H
