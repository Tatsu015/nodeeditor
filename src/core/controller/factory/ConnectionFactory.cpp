#include "ConnectionFactory.h"
#include "Connection.h"
#include "FigureNamePublisher.h"

ConnectionFactory* ConnectionFactory::getInstance() {
  static ConnectionFactory s;
  return &s;
}

void ConnectionFactory::addConnection(Connection* connection) {
  m_connectionMap[connection->connectionType()] = connection;
}

Connection* ConnectionFactory::createConnection(const Sheet* sheet, const QString& type, const QString& name,
                                                const QString& id) {
  Connection* connection;
  if (id.isEmpty()) {
    connection = m_connectionMap[type]->create();
  } else {
    connection = m_connectionMap[type]->create(id);
  }

  QString newName = name;
  if (newName.isEmpty()) {
    newName = FigureNamePublisher::getInstance()->createName(sheet, connection->connectionType());
  }

  connection->setName(newName);

  return connection;
}

ConnectionFactory::ConnectionFactory() {
}

ConnectionFactory::~ConnectionFactory() {
}
