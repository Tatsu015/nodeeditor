#include "Connector.h"
#include <QPen>
#include <QBrush>

const static int CONNECTOR_RADIUS = 10;

Connector::Connector(QGraphicsItem* parent) :
    QGraphicsPathItem(parent)
{
    setPen(QPen(Qt::gray, 1));
    setBrush(QBrush(Qt::gray));

    QPainterPath path;
    path.addEllipse(-CONNECTOR_RADIUS, -CONNECTOR_RADIUS , CONNECTOR_RADIUS, CONNECTOR_RADIUS);
    setPath(path);
}

Connector::~Connector()
{

}

void Connector::setPos(const QPointF pos)
{
    setPos(pos + QPointF(CONNECTOR_RADIUS, CONNECTOR_RADIUS)*0.5);
}
