#include "PortFactory.h"
#include "NamePublisher.h"

PortFactory *PortFactory::getInstance() {
  static PortFactory s;
  return &s;
}

void PortFactory::addPort(Port* port)
{
  m_portMap[port->portType()] = port;
  NamePublisher::getInstance()->addBaseName(port->portType());
}

Port*PortFactory::createPort(const QString& type, const IO io, uint32_t number, QGraphicsItem* parent)
{
  Port *port = m_portMap[type]->create(io, number, parent);

  QString newName = NamePublisher::getInstance()->createName(port->portType());
  port->setName(newName);

  return port;
}

PortFactory::PortFactory() {}

PortFactory::~PortFactory() {}
