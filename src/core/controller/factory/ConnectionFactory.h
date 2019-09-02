#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QMap>
#include <QString>

class Sheet;
class Connection;

class ConnectionFactory {
public:
  static ConnectionFactory* getInstance();

  void addConnection(Connection* connection);
  Connection* createConnection(const Sheet* sheet, const QString& type, const QString& name = "",
                               const QString& id = "");

private:
  QMap<QString, Connection*> m_connectionMap;

private:
  ConnectionFactory();
  ~ConnectionFactory();
};

#endif // CONNECTIONFACTORY_H
