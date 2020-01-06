#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QIcon>
#include <QMap>
#include <QString>

class Sheet;
class AbstractConnection;

class ConnectionFactory {
public:
  static ConnectionFactory* getInstance();

  void addConnection(AbstractConnection* connection);
  AbstractConnection* createConnection(const Sheet* sheet, const QString& type, const QString& name = "",
                                       const QString& id = "");
  AbstractConnection* createConnection(const QString& type, const QString& name, const QString& id);
  QIcon createIcon(const QString& type) const;
  QStringList connectionTypes() const;

private:
  QMap<QString, AbstractConnection*> m_connectionMap;
  QStringList m_nodeTypes;

private:
  ConnectionFactory();
  ~ConnectionFactory();
};

#endif // CONNECTIONFACTORY_H
