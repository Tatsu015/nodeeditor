#include "ConnectorFactory.h"
#include "NamePublisher.h"

ConnectorFactory* ConnectorFactory::getInstance() {
  static ConnectorFactory s;
  return &s;
}

void ConnectorFactory::addConnector(Connector* connector) {
  m_connectorMap[connector->connectorType()] = connector;
  NamePublisher::getInstance()->addBaseName(connector->connectorType());
}

Connector* ConnectorFactory::createConnector(const QString& type, QGraphicsItem* parent) {
  Connector* connector = m_connectorMap[type]->create(parent);

  QString newName = NamePublisher::getInstance()->createName(connector->connectorType());
  connector->setName(newName);

  return connector;
}

ConnectorFactory::ConnectorFactory() {}

ConnectorFactory::~ConnectorFactory() {}
