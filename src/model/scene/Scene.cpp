#include "Scene.h"
#include "InNode.h"
#include "OutNode.h"
#include "HiddenNode.h"
#include "Connection.h"
#include "Connector.h"
#include "Port.h"
#include "Tool.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "Define.h"
#include "NodeFactory.h"
#include "ConnectionFactory.h"

Scene::Scene(QObject* parent):
    QGraphicsScene(-750,-1000,2000,2000,parent),
    m_isControlPressed(false)
{
    addLine(-1000, 0, 1000, 0, QPen(Qt::gray));
    addLine(0, -1000, 0, 1000, QPen(Qt::gray));

    //    AutoSet();
}

Scene::~Scene()
{
}

void Scene::autoSet()
{
    QGraphicsSceneMouseEvent event;

    Tool::getInstance()->changeActiveTool("In");
    event.setScenePos(QPointF(0,0));
    mouseDoubleClickEvent(&event);
    event.setScenePos(QPointF(0,50));
    mouseDoubleClickEvent(&event);

    Tool::getInstance()->changeActiveTool("Hidden");
    event.setScenePos(QPointF(100,25));
    mouseDoubleClickEvent(&event);
    event.setScenePos(QPointF(200,75));
    mouseDoubleClickEvent(&event);

    Tool::getInstance()->changeActiveTool("Out");
    event.setScenePos(QPointF(400,0));
    mouseDoubleClickEvent(&event);
    event.setScenePos(QPointF(400,100));
    mouseDoubleClickEvent(&event);

    Tool::getInstance()->changeActiveTool("In");
    event.setScenePos(QPointF(0,125));
    mouseDoubleClickEvent(&event);

    Tool::getInstance()->changeActiveTool("Hidden");
    event.setScenePos(QPointF(300,100));
    mouseDoubleClickEvent(&event);

    event.setScenePos(m_nodes[0]->ports().at(0)->centerScenePos());
    mousePressEvent(&event);
    event.setScenePos(m_nodes[2]->ports().at(0)->centerScenePos());
    mouseReleaseEvent(&event);

    event.setScenePos(m_nodes[1]->ports().at(0)->centerScenePos());
    mousePressEvent(&event);
    event.setScenePos(m_nodes[2]->ports().at(1)->centerScenePos());
    mouseReleaseEvent(&event);

    event.setScenePos(m_nodes[2]->ports().at(2)->centerScenePos());
    mousePressEvent(&event);
    event.setScenePos(m_nodes[3]->ports().at(0)->centerScenePos());
    mouseReleaseEvent(&event);

    event.setScenePos(m_nodes[2]->ports().at(2)->centerScenePos());
    mousePressEvent(&event);
    event.setScenePos(m_nodes[4]->ports().at(0)->centerScenePos());
    mouseReleaseEvent(&event);

    event.setScenePos(m_nodes[6]->ports().at(0)->centerScenePos());
    mousePressEvent(&event);
    event.setScenePos(m_nodes[7]->ports().at(1)->centerScenePos());
    mouseReleaseEvent(&event);

    event.setScenePos(m_nodes[3]->ports().at(2)->centerScenePos());
    mousePressEvent(&event);
    event.setScenePos(m_nodes[7]->ports().at(0)->centerScenePos());
    mouseReleaseEvent(&event);

    event.setScenePos(m_nodes[7]->ports().at(2)->centerScenePos());
    mousePressEvent(&event);
    event.setScenePos(m_nodes[5]->ports().at(0)->centerScenePos());
    mouseReleaseEvent(&event);

    event.setScenePos(m_nodes[7]->ports().at(2)->centerScenePos());
    mousePressEvent(&event);
    event.setScenePos(m_nodes[3]->ports().at(1)->centerScenePos());
    mouseReleaseEvent(&event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_startPort = findPort(event->scenePos());
    if(!m_startPort){
        QGraphicsScene::mousePressEvent(event);
        return;
    }

    QPointF startPortCenterPos = m_startPort->centerScenePos();

    m_tmpConnection = ConnectionFactory::getInstance()->createConnection(CONNECTION);
    m_tmpConnection->setStartPos(startPortCenterPos);
    m_tmpConnection->setEndPos(startPortCenterPos);
    addConnection(m_tmpConnection);

    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(!m_tmpConnection){
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }
    m_tmpConnection->setEndPos(event->scenePos());

    Connection* endConnection = findConnection(event->scenePos());
    if(endConnection){
        if(!m_tmpConnector){
            m_tmpConnector = new Connector();
            QPointF ofs(m_tmpConnector->boundingRect().center());
            m_tmpConnector->setPos(event->scenePos() - ofs);
            addItem(m_tmpConnector);
        }
    }
    else{
        if(m_tmpConnector){
            removeItem(m_tmpConnector);
            m_tmpConnector->setParentItem(nullptr);
            m_tmpConnector = nullptr;
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(!m_tmpConnection){
        QGraphicsScene::mouseReleaseEvent(event);
        return;
    }

    Port* endPort = findPort(event->scenePos());
    if(endPort){
        if(Input == endPort->io()){
            m_tmpConnection->setStartPort(m_startPort);
            m_tmpConnection->setEndPort(endPort);
        }
        else{
            m_tmpConnection->setStartPort(endPort);
            m_tmpConnection->setEndPort(m_startPort);
        }

        m_startPort->addConnection(m_tmpConnection);
        endPort->addConnection(m_tmpConnection);

        m_tmpConnection = nullptr;

        QGraphicsScene::mouseReleaseEvent(event);
        return;
    }

    if(m_tmpConnector){
        //        Connection* endConnection = FindConnection(event->scenePos());
        //        endConnection->AddConnector(m_tmpConnector);

        //        m_tmpConnection->SetStartPort(m_startPort);
        //        m_tmpConnection->SetEndPort(nullptr);

        //        m_startPort->AddConnection(m_tmpConnection);

        //        m_tmpConnection = nullptr;

        //        QGraphicsScene::mouseReleaseEvent(event);
        //        return;
    }

    removeItem(m_tmpConnection);
    delete m_tmpConnection;
    m_tmpConnection = nullptr;
    QGraphicsScene::mousePressEvent(event);
    return;

}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if(existPort(event->scenePos())){
        QGraphicsScene::mouseDoubleClickEvent(event);
        return;
    }

    createNode(event->scenePos());

    QGraphicsScene::mouseDoubleClickEvent(event);
}

void Scene::keyPressEvent(QKeyEvent* event)
{
    if(Qt::Key_Delete == event->key()){
        foreach (QGraphicsItem* item, selectedItems()) {
            removeNode(dynamic_cast<AbstractNode*>(item));
        }
    }
    else if(Qt::Key_Control == event->key()){
        m_isControlPressed = true;
    }
    else if(Qt::Key_A == event->key()){
        if(m_isControlPressed){
            foreach (AbstractNode* node, nodes()) {
                node->setSelected(true);
            }
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent* event)
{
    if(Qt::Key_Control == event->key()){
        m_isControlPressed = false;
    }

    QGraphicsScene::keyReleaseEvent(event);
}

Port*Scene::findPort(QPointF scenePos)
{
    QList<QGraphicsItem *> pressedItems = items(scenePos);

    Port* port = nullptr;
    foreach (QGraphicsItem* item, pressedItems) {
        port = dynamic_cast<Port*>(item);
        if(port){
            return port;
        }
    }
    return nullptr;
}

Port*Scene::findStartPort(QPointF scenePos)
{
    QList<QGraphicsItem *> pressedItems = items(scenePos);

    Port* port = nullptr;
    foreach (QGraphicsItem* item, pressedItems) {
        port = dynamic_cast<Port*>(item);
        if(port){
            if(Output == port->io()){
                return port;
            }
        }
    }
    return nullptr;
}

Port*Scene::findEndPort(QPointF scenePos)
{
    QList<QGraphicsItem *> pressedItems = items(scenePos);

    Port* port = nullptr;
    foreach (QGraphicsItem* item, pressedItems) {
        port = dynamic_cast<Port*>(item);
        if(port){
            if(Input == port->io()){
                return port;
            }
        }
    }
    return nullptr;
}

//QList<Port*> Scene::aroundEndPorts(QPointF scenePos)
//{
//    QList<QGraphicsItem *> aroundItems = items(scenePos.x() - 20,
//                                               scenePos.y() - 20,
//                                               40,
//                                               40,
//                                               Qt::IntersectsItemShape,
//                                               Qt::AscendingOrder);

//    QList<Port*> aroundEndPorts;
//    foreach (QGraphicsItem* item, aroundItems) {
//        Port* port = dynamic_cast<Port*>(item);
//        if(port){
//            if(Input == port->io()){
//                aroundEndPorts << port;
//            }
//        }
//    }
//    return aroundEndPorts;
//}

Connection*Scene::findConnection(QPointF scenePos)
{
    QList<QGraphicsItem *> pressedItems = items(scenePos);

    Connection* connection = nullptr;
    foreach (QGraphicsItem* item, pressedItems) {
        connection = dynamic_cast<Connection*>(item);
        if(connection && (m_tmpConnection != connection)){
            qDebug() << "Find Connection!";
            return connection;
        }
    }
    return nullptr;
}

QList<AbstractNode*> Scene::findNodes(QPointF scenePos)
{
    QList<AbstractNode*> nodes;
    foreach (QGraphicsItem* item, items(scenePos)) {
        AbstractNode* node = dynamic_cast<AbstractNode*>(item);
        if(node){
            nodes << node;
        }
    }

    return nodes;
}

bool Scene::existNode(QPointF scenePos)
{
    foreach (QGraphicsItem* item, items(scenePos)) {
        AbstractNode* node = dynamic_cast<AbstractNode*>(item);
        if(node){
            return true;
        }
    }

    return false;
}

bool Scene::existPort(QPointF scenePos)
{
    foreach (QGraphicsItem* item, items(scenePos)) {
        Port* port = dynamic_cast<Port*>(item);
        if(port){
            return true;
        }
    }

    return false;
}

void Scene::showConnector(QPointF scenePos)
{
    if(!m_tmpConnector){
        m_tmpConnector = new Connector();
        addItem(m_tmpConnector);
    }
    m_tmpConnector->setPos(scenePos);
}

QList<AbstractNode*> Scene::nodes() const
{
    return m_nodes;
}

void Scene::addNode(AbstractNode *node)
{
    m_nodes << node;
    addItem(node);
}

void Scene::removeNode(AbstractNode* node)
{
    foreach (Port* removeNodePort, node->ports()) {
        foreach (Connection* connection, removeNodePort->connections()) {
            removeNodePort->removeConnection(connection);
            Port* oppositeSidePort = connection->oppositeSidePort(removeNodePort);
            oppositeSidePort->removeConnection(connection);
            removeItem(connection);
            delete connection;
        }
    }
    m_nodes.removeOne(node);
    removeItem(node);
    delete node;
}

QList<Connection *> Scene::connections() const
{
    return m_connections;
}

void Scene::addConnection(Connection *connection)
{
    m_connections.append(connection);
    addItem(connection);
}

void Scene::removeConnection(Connection *connection)
{
    connection->startPort()->removeConnection(connection);
    connection->endPort()->removeConnection(connection);

    connection->removeStartPort();
    connection->removeEndPort();

    m_connections.removeOne(connection);
}

void Scene::createNode(QPointF scenePos)
{
    QString activeTool = Tool::getInstance()->activeTool();

    AbstractNode* node = nullptr;
    node = NodeFactory::getInstance()->createNode(activeTool);

    QPointF ofs(node->boundingRect().center());
    node->setPos(scenePos - ofs);
    addNode(node);
}
