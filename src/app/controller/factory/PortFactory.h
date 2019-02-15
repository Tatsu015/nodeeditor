#ifndef PortFactory_H
#define PortFactory_H

#include <QMap>
#include <QString>
#include "Port.h"

class PortFactory {
 public:
  static PortFactory* getInstance();

  void addPort(Port* port);
  Port* createPort(const QString& type, const IO io, uint32_t number, QGraphicsItem* parent);

 private:
  QMap<QString, Port*> m_portMap;

 private:
  PortFactory();
  ~PortFactory();
};

#endif  // PortFactory_H
