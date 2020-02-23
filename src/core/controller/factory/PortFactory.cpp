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
  // port number start from 0 origin
  int32_t number = parent->portCount() + 1;
  Port* port = m_portMap[type]->create(io, number, parent, isInverted, true);
  return port;
}

Port* PortFactory::createPort(const QString& type, const IO io, const int32_t number, AbstractNode* parent,
                              const bool isInverted) {
  Port* port = m_portMap[type]->create(io, number, parent, isInverted, true);
  return port;
}

PortFactory::PortFactory() {
}

PortFactory::~PortFactory() {
}
