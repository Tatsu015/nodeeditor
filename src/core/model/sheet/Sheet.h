#ifndef SHEET_H
#define SHEET_H

#include <QJsonObject>
#include <QList>
#include <QString>

class AbstractNode;
class AbstractConnection;

class Sheet {
public:
  Sheet();
  ~Sheet();

  Sheet* create();
  Sheet* create(const QString& name, const QString& id);

  QString id() const;

  QList<AbstractNode*> nodes() const;
  AbstractNode* node(const QString& nodeName) const;
  void addNode(AbstractNode* node);
  void removeNode(AbstractNode* node);
  QStringList nodeNames() const;

  QList<AbstractNode*> inNodes() const;
  int32_t inNodeCount() const;
  QList<AbstractNode*> outNodes() const;
  int32_t outNodeCount() const;

  AbstractConnection* connection(const QString& connectionName) const;
  QList<AbstractConnection*> connections() const;
  void addConnection(AbstractConnection* connection);
  void removeConnection(AbstractConnection* connection);
  QStringList connectionNames() const;

  QString name() const;
  void setName(const QString& name);

  bool contain(const QString& figureName) const;

  QJsonObject toJsonObj();
  QJsonObject toSelectedJsonObj();

private:
  QString m_id = "";
  QString m_name = "Untitled";
  QList<AbstractNode*> m_nodes;
  QList<AbstractConnection*> m_connections;
};

#endif // SHEET_H
