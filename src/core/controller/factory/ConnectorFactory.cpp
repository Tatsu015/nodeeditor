#include "ConnectorFactory.h"

ConnectorFactory* ConnectorFactory::getInstance() {
  static ConnectorFactory s;
  return &s;
}

void ConnectorFactory::addConnector(Connector* connector) {
  m_connectorMap[connector->connectorType()] = connector;
}

Connector* ConnectorFactory::createConnector(const QString& type, QGraphicsItem* parent) {
  Connector* connector = m_connectorMap[type]->create(parent);

  return connector;
}

ConnectorFactory::ConnectorFactory() {
}

ConnectorFactory::~ConnectorFactory() {
}
