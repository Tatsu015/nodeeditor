#ifndef CONNECTIONCREATIONTOOL_H
#define CONNECTIONCREATIONTOOL_H

#include "AbstractTool.h"
#include <QPointF>

class Port;
class Connection;

class ConnectionCreationTool : public AbstractTool
{
public:
    ConnectionCreationTool();
    virtual ~ConnectionCreationTool();

    virtual void mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent *event);

private:
    void redrawTmpConnection(Scene *scene, Port* startPort, QPointF nowScenePos);
    void decideConnection();
    void removeTmpConnection();

private:
    Port* m_startPort = nullptr;
    Connection*  m_tmpConnection  = nullptr;
};

#endif // CONNECTIONCREATIONTOOL_H
