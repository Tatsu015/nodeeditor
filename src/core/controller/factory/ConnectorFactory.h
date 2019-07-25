#ifndef ConnectorFactory_H
#define ConnectorFactory_H

#include "Connector.h"
#include <QMap>
#include <QString>

class ConnectorFactory {
public:
  static ConnectorFactory* getInstance();

  void addConnector(Connector* connector);
  Connector* createConnector(const QString& type, QGraphicsItem* parent = nullptr);

private:
  QMap<QString, Connector*> m_connectorMap;

private:
  ConnectorFactory();
  ~ConnectorFactory();
};

#endif // ConnectorFactory_H
