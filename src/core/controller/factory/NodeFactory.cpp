#include "NodeFactory.h"
#include "AbstractNode.h"
#include "FigureNamePublisher.h"

NodeFactory* NodeFactory::getInstance() {
  static NodeFactory s;
  return &s;
}

void NodeFactory::addNode(AbstractNode* node) {
  m_nodeMap[node->nodeType()] = node;
  m_nodeTypes.append(node->nodeType());
}

AbstractNode* NodeFactory::createNode(const Sheet* sheet, const QString& type, const QString& name, const QString& id) {
  AbstractNode* node;
  if (id.isEmpty()) {
    node = m_nodeMap[type]->create();
  } else {
    node = m_nodeMap[type]->create(id);
  }

  QString newName = name;
  if (newName.isEmpty()) {
    newName = FigureNamePublisher::getInstance()->createName(sheet, node->nodeType());
  }

  node->setName(newName);
  node->setupNameText();

  return node;
}

QStringList NodeFactory::nodeTypes() const {
  return m_nodeTypes;
}

NodeFactory::NodeFactory() {
}

NodeFactory::~NodeFactory() {
}
