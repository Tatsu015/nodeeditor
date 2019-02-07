#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <QMap>
#include <QString>

class AbstractNode;

class NodeFactory {
 public:
  static NodeFactory* getInstance();

  void addNode(const QString& type, AbstractNode* node);
  AbstractNode* createNode(const QString& type, QString name = "");

 private:
  QMap<QString, AbstractNode*> m_nodeMap;

 private:
  NodeFactory();
  ~NodeFactory();
};

#endif  // NODEFACTORY_H
