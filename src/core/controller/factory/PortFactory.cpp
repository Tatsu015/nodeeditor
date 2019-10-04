#include "PortFactory.h"
#include "AbstractNode.h"

PortFactory* PortFactory::getInstance() {
  static PortFactory s;
  return &s;
}

void PortFactory::addPort(Port* port) {
  m_portMap[port->portType()] = port;
}

Port* PortFactory::createPort(const QString& type, const IO io, AbstractNode* parent, const bool isInverted) {
  int32_t number = parent->portCount();
  Port* port = m_portMap[type]->create(io, number, parent);
  port->invert(isInverted);
  return port;
}

PortFactory::PortFactory() {
}

PortFactory::~PortFactory() {
}
