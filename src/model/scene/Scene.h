#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class AbstractNode;
class InNode;
class Connection;
class Connector;
class Port;

class Scene : public QGraphicsScene
{
public:
    Scene(QObject *parent = nullptr);
    virtual ~Scene();

    void autoSet();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    QList<AbstractNode*> nodes() const;
    void addNode(AbstractNode *node);
    void removeNode(AbstractNode* node);

    QList<Connection *> connections() const;
    void addConnection(Connection *connection);
    void removeConnection(Connection* connection);

private:
    Port* findPort(QPointF scenePos);
    Port* findStartPort(QPointF scenePos);
    Port* findEndPort(QPointF scenePos);

    QList<AbstractNode*> findNodes(QPointF scenePos);

    Connection* findConnection(QPointF scenePos);

//    QList<Port*> aroundEndPorts(QPointF scenePos);

    bool existInNode(QPointF scenePos);
    bool existNode(QPointF scenePos);
    bool existPort(QPointF scenePos);

    void createNode(QPointF scenePos);

    void showConnector(QPointF scenePos);

private:
    QList<AbstractNode*> m_nodes;
    QList<Connection*>   m_connections;
    Connection*  m_tmpConnection  = nullptr;
    Connector*   m_tmpConnector   = nullptr;
    Port*        m_startPort      = nullptr;
    bool m_isControlPressed;
};

#endif // SCENE_H
