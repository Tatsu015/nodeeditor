#include "NodeCreateTool.h"
#include <QGraphicsSceneMouseEvent>
#include <QAction>
#include "NodeFactory.h"
#include "AbstractNode.h"
#include "Scene.h"
#include "Define.h"

NodeCreateTool::NodeCreateTool():
    AbstractTool()
{
    m_nodeTypes.append(NODE_IN    );
    m_nodeTypes.append(NODE_OUT   );
    m_nodeTypes.append(NODE_HIDDEN);
}

NodeCreateTool::~NodeCreateTool()
{
}

void NodeCreateTool::mousePressEvent(Scene* scene, QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(scene);
    Q_UNUSED(event);
}

void NodeCreateTool::mouseMoveEvent(Scene* scene, QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(scene);
    Q_UNUSED(event);
}

void NodeCreateTool::mouseReleaseEvent(Scene* scene, QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(scene);
    Q_UNUSED(event);
}

void NodeCreateTool::mouseDoubleClickEvent(Scene* scene, QGraphicsSceneMouseEvent *event)
{
    AbstractNode* node = NodeFactory::getInstance()->createNode(m_activeNodeType);
    QPointF ofs(node->boundingRect().center());
    scene->addNode(node, QPointF(event->scenePos() - ofs));
}

QStringList NodeCreateTool::nodeTypes() const
{
    return m_nodeTypes;
}

void NodeCreateTool::setActiveNodeType(const QString &activeNodeType)
{
    m_activeNodeType = activeNodeType;
}

