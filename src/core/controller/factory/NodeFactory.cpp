#include "NodeFactory.h"
#include "AbstractNode.h"
#include "FigureNamePublisher.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

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
  node->setup();

  return node;
}

AbstractNode* NodeFactory::createNode(const QString& type, const QString& name, const QString& id) {
  AbstractNode* node = m_nodeMap[type]->create(id);
  node->setName(name);
  node->setup();

  return node;
}

QIcon NodeFactory::createIcon(const QString& type) const {
  AbstractNode* node = m_nodeMap[type];
  QPixmap pixmap(node->boundingRect().size().toSize() + QSize(10, 10));
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);
  QStyleOptionGraphicsItem opt;
  node->paint(&painter, &opt);

  return QIcon(pixmap);
}

QStringList NodeFactory::nodeTypes() const {
  return m_nodeTypes;
}

NodeFactory::NodeFactory() {
}

NodeFactory::~NodeFactory() {
}
