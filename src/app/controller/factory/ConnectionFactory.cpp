#include "ConnectionFactory.h"
#include "Connection.h"
#include "NamePublisher.h"

ConnectionFactory *ConnectionFactory::getInstance() {
  static ConnectionFactory s;
  return &s;
}

void ConnectionFactory::addConnection(Connection *connection) {
  m_connectionMap[connection->connectionType()] = connection;
  NamePublisher::getInstance()->addBaseName(connection->connectionType());
}

Connection *ConnectionFactory::createConnection(const QString &type, QString name) {
  Connection *connection = m_connectionMap[type]->create();

  QString newName = name;
  if (newName.isEmpty()) {
    newName = NamePublisher::getInstance()->createName(connection->connectionType());
  } else {
    NamePublisher::getInstance()->updateLastNumber(name);
  }

  connection->setName(newName);

  return connection;
}

ConnectionFactory::ConnectionFactory() {}

ConnectionFactory::~ConnectionFactory() {}
