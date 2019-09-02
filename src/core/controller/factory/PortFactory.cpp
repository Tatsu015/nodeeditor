#include "PortFactory.h"

PortFactory* PortFactory::getInstance() {
  static PortFactory s;
  return &s;
}

void PortFactory::addPort(Port* port) {
  m_portMap[port->portType()] = port;
}

Port* PortFactory::createPort(const QString& type, const IO io, uint32_t number, QGraphicsItem* parent) {
  Port* port = m_portMap[type]->create(io, number, parent);
  return port;
}

PortFactory::PortFactory() {
}

PortFactory::~PortFactory() {
}
