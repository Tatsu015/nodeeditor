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

    if(name.isEmpty()){
        QString newName = NamePublisher::getInstance()->createName(node->nodeType());
        node->setName(newName);
    }
    else{
        node->setName(name);
    }

    node->setupNameText();

    return node;
}

NodeFactory::NodeFactory()
{
}

NodeFactory::~NodeFactory()
{
}

