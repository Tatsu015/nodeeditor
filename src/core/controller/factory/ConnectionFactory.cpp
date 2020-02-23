#include "ConnectionFactory.h"
#include "AbstractConnection.h"
#include "SerialNumberNamePublisher.h"
#include "Sheet.h"

ConnectionFactory* ConnectionFactory::getInstance() {
  static ConnectionFactory s;
  return &s;
}

void ConnectionFactory::addConnection(AbstractConnection* connection) {
  m_connectionMap[connection->connectionType()] = connection;
  m_nodeTypes.append(connection->connectionType());
}

AbstractConnection* ConnectionFactory::createConnection(const Sheet* sheet, const QString& type, const QString& name,
                                                        const QString& id) {
  AbstractConnection* connection = nullptr;
  if (id.isEmpty()) {
    connection = m_connectionMap[type]->create();
  } else {
    connection = m_connectionMap[type]->create(id);
  }

  QString newName = name;
  if (newName.isEmpty()) {
    newName =
        SerialNumberNamePublisher::getInstance()->createName(sheet->connectionNames(), connection->connectionType());
  }

  connection->setName(newName);
  connection->setup();

  return connection;
}

AbstractConnection* ConnectionFactory::createConnection(const QString& type, const QString& name, const QString& id) {
  AbstractConnection* connection = nullptr;
  connection = m_connectionMap[type]->create(id);
  connection->setName(name);
  connection->setup();

  return connection;
}

QIcon ConnectionFactory::createIcon(const QString& type) const {
  AbstractConnection* connection = m_connectionMap[type];

  return QIcon(connection->pixmap());
}

QStringList ConnectionFactory::connectionTypes() const {
  return m_nodeTypes;
}

ConnectionFactory::ConnectionFactory() {
}

ConnectionFactory::~ConnectionFactory() {
}
