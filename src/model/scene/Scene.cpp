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
#include "NodeCreateTool.h"
#include "Editor.h"
#include "AbstractTool.h"



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
    if(!Editor::getInstance()->activeTool()->isUsing()){
        if(existNode(event->scenePos())){
            qDebug() << "node";
            Editor::getInstance()->changeActiveTool("NODE");
        }
        else if(existPort(event->scenePos())){
            qDebug() << "port";
            Editor::getInstance()->changeActiveTool("CONNECTION");
        }
        else{
            qDebug() << "none";
            Editor::getInstance()->changeActiveTool("NODE");
        }
    }

    Editor::getInstance()->activeTool()->mousePressEvent(this, event);
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    Editor::getInstance()->activeTool()->mouseMoveEvent(this, event);
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    Editor::getInstance()->activeTool()->mouseReleaseEvent(this, event);
    Editor::getInstance()->changeDefaultTool();
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    Editor::getInstance()->activeTool()->mouseDoubleClickEvent(this, event);
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

Connection*Scene::findConnection(QPointF scenePos)
{
    QList<QGraphicsItem *> pressedItems = items(scenePos);

    Connection* connection = nullptr;
    foreach (QGraphicsItem* item, pressedItems) {
        connection = dynamic_cast<Connection*>(item);
        if(connection && (m_tmpConnection != connection)){
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

AbstractNode *Scene::findNode(const QString &nodeName)
{
    foreach (AbstractNode* node, m_nodes) {
        if(nodeName == node->name()){
            return node;
        }
    }
    return nullptr;
}

bool Scene::existNode(QPointF scenePos)
{
    if(0 < findNodes(scenePos).count()){
        return true;
    }
    return false;
}

bool Scene::existPort(QPointF scenePos)
{
    if(findPort(scenePos)){
        return true;
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

void Scene::addNode(AbstractNode *node, QPointF scenePos)
{
    node->setPos(scenePos);
    m_nodes << node;
    addItem(node);
}

void Scene::removeNode(AbstractNode* node)
{
    foreach (Port* removeNodePort, node->ports()) {
        foreach (Connection* connection, removeNodePort->connections()) {
            removeConnection(connection);
        }
    }
    m_nodes.removeOne(node);
    removeItem(node);
    delete node;
    node = nullptr;
}

QList<Connection *> Scene::connections() const
{
    return m_connections;
}

void Scene::addConnection(Connection *connection, Port *startPort)
{
    connection->setStartPort(startPort);
    connection->setStartPos(startPort->centerScenePos());
    startPort->addConnection(connection);

    connection->setEndPos(startPort->centerScenePos());

    m_connections.append(connection);
    addItem(connection);
}

void Scene::addConnection(Connection *connection, Port *startPort, Port *endPort)
{
    connection->setStartPort(startPort);
    connection->setStartPos(startPort->centerScenePos());
    startPort->addConnection(connection);

    connection->setEndPort(endPort);
    connection->setEndPos(endPort->centerScenePos());
    endPort->addConnection(connection);

    m_connections.append(connection);
    addItem(connection);
}

void Scene::addConnection(const QString &startNodeName, int32_t startPortNumber, const QString &endNodeName, int32_t endPortNumber)
{
    AbstractNode* startNode = findNode(startNodeName);
    AbstractNode* endNode   = findNode(endNodeName);

    Port* startPort = startNode->port(startPortNumber);
    Port* endPort   = endNode->port(endPortNumber);

    Connection* connection = new Connection();

    addConnection(connection, startPort, endPort);

    connection->updatePath();
}

void Scene::removeConnection(Connection *connection)
{
    // when connection is tmp connection,
    // start or end port maybe become null pointer
    Port* startPort = connection->startPort();
    if(startPort){
        startPort->removeConnection(connection);
        connection->removeStartPort();
    }

    Port* endPort = connection->endPort();
    if(endPort){
        endPort->removeConnection(connection);
        connection->removeEndPort();
    }

    m_connections.removeOne(connection);
    delete connection;
    connection = nullptr;
}

