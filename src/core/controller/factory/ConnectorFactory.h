#ifndef CONNECTORFACTORY_H
#define CONNECTORFACTORY_H

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

#endif // CONNECTORFACTORY_H
