#ifndef PORTFACTORY_H
#define PORTFACTORY_H

#include "Port.h"
#include <QMap>
#include <QString>

class PortFactory {
public:
  static PortFactory* getInstance();

  void addPort(Port* port);
  Port* createPort(const QString& type, const IO io, AbstractNode* parent, const bool isInverted = false);
  Port* createPort(const QString& type, const IO io, const int32_t number, AbstractNode* parent,
                   const bool isInverted = false);

private:
  QMap<QString, Port*> m_portMap;

private:
  PortFactory();
  ~PortFactory();
};

#endif // PORTFACTORY_H
