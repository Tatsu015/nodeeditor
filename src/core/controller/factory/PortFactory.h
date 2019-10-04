#ifndef PortFactory_H
#define PortFactory_H

#include "Port.h"
#include <QMap>
#include <QString>

class PortFactory {
public:
  static PortFactory* getInstance();

  void addPort(Port* port);
  Port* createPort(const QString& type, const IO io, AbstractNode* parent, const bool isInverted = false);

private:
  QMap<QString, Port*> m_portMap;

private:
  PortFactory();
  ~PortFactory();
};

#endif // PortFactory_H
