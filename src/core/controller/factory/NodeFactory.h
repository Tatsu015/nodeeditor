#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <QMap>
#include <QString>

class Sheet;
class AbstractNode;

class NodeFactory {
public:
  static NodeFactory* getInstance();

  void addNode(AbstractNode* node);
  AbstractNode* createNode(const Sheet* sheet, const QString& type, const QString& name = "", const QString& id = "");
  AbstractNode* createNode(const QString& type, const QString& name, const QString& id);
  QStringList nodeTypes() const;

private:
  QMap<QString, AbstractNode*> m_nodeMap;
  QStringList m_nodeTypes;

private:
  NodeFactory();
  ~NodeFactory();
};

#endif // NODEFACTORY_H
