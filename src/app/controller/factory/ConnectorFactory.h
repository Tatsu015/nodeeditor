#ifndef ConnectorFactory_H
#define ConnectorFactory_H

#include <QMap>
#include <QString>
#include "Connector.h"

class ConnectorFactory {
 public:
  static ConnectorFactory* getInstance();

  void addConnector(Connector* connector);
  Connector* createConnector(const QString& type, QGraphicsItem* parent);

 private:
  QMap<QString, Connector*> m_connectorMap;

 private:
  ConnectorFactory();
  ~ConnectorFactory();
};

#endif  // ConnectorFactory_H
