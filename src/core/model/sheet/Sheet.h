#ifndef SHEET_H
#define SHEET_H

#include <QList>
#include <QString>

class AbstractNode;
class Connection;

class Sheet {
public:
  Sheet();
  ~Sheet();

  Sheet* create();
  Sheet* create(const QString& id);

  QString id() const;

  QList<AbstractNode*> nodes() const;
  AbstractNode* node(const QString& nodeName) const;
  void addNode(AbstractNode* node);
  void removeNode(AbstractNode* node);

  Connection* connection(const QString& connectionName) const;
  QList<Connection*> connections() const;
  void addConnection(Connection* connection);
  void removeConnection(Connection* connection);

  QString name() const;
  void setName(const QString& name);

  bool contain(const QString& figureName) const;

private:
  QString m_id = "";
  QString m_name = "Untitled";
  QList<AbstractNode*> m_nodes;
  QList<Connection*> m_connections;
};

#endif // SHEET_H
