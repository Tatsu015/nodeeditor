#include "NodeFactory.h"
#include "AbstractNode.h"
#include "NamePublisher.h"

NodeFactory* NodeFactory::getInstance()
{
    static NodeFactory s;
    return &s;
}

void NodeFactory::addNode(const QString &type, AbstractNode *node)
{
    m_nodeMap[type] = node;
}

AbstractNode *NodeFactory::createNode(const QString &type, QString name)
{
    AbstractNode* node = m_nodeMap[type]->create();

    QString newName = name;
    if(name.isEmpty()){
        newName = NamePublisher::getInstance()->createName(node->nodeType());
    }

    node->setName(newName);
    node->setupNameText();

    NamePublisher::getInstance()->updateLastNumber(name);

    return node;
}

NodeFactory::NodeFactory()
{
}

NodeFactory::~NodeFactory()
{
}

