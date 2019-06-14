#include "NodeFactory.h"
#include "AbstractNode.h"
#include "NamePublisher.h"

NodeFactory* NodeFactory::getInstance() {
  static NodeFactory s;
  return &s;
}

void NodeFactory::addNode(AbstractNode* node) {
  m_nodeMap[node->nodeType()] = node;
  NamePublisher::getInstance()->addBaseName(node->nodeType());
}

AbstractNode* NodeFactory::createNode(const QString& type, QString name) {
  AbstractNode* node = m_nodeMap[type]->create();

  QString newName = name;
  if (newName.isEmpty()) {
    newName = NamePublisher::getInstance()->createName(node->nodeType());
  } else {
    NamePublisher::getInstance()->updateLastNumber(name);
  }

  node->setName(newName);
  node->setupNameText();

  return node;
}

NodeFactory::NodeFactory() {
}

NodeFactory::~NodeFactory() {
}
