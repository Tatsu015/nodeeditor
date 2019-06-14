#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QMap>
#include <QString>

class Connection;

class ConnectionFactory {
public:
  static ConnectionFactory* getInstance();

  void addConnection(Connection* connection);
  Connection* createConnection(const QString& type, QString name = "");

private:
  QMap<QString, Connection*> m_connectionMap;

private:
  ConnectionFactory();
  ~ConnectionFactory();
};

#endif // CONNECTIONFACTORY_H
