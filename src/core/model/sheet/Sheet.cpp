#include "Sheet.h"
#include "AbstractConnection.h"
#include "AbstractNode.h"
#include "Port.h"
#include "ProjectKeyDefine.h"
#include <QUuid>

Sheet::Sheet() {
}

Sheet::~Sheet() {
}

Sheet* Sheet::create() {
  QString uuid = QUuid::createUuid().toString();
  return create(uuid, uuid);
}

Sheet* Sheet::create(const QString& name, const QString& id) {
  Sheet* sheet = new Sheet();
  sheet->m_id = id;
  sheet->m_name = name;
  return sheet;
}

QString Sheet::id() const {
  return m_id;
}

QList<AbstractNode*> Sheet::nodes() const {
  return m_nodes;
}

AbstractNode* Sheet::node(const QString& nodeName) const {
  foreach (AbstractNode* node, m_nodes) {
    if (nodeName == node->name()) {
      return node;
    }
  }
  return nullptr;
}

void Sheet::addNode(AbstractNode* node) {
  m_nodes << node;
}

void Sheet::removeNode(AbstractNode* node) {
  m_nodes.removeOne(node);
}

QStringList Sheet::nodeNames() const {
  QStringList names;
  foreach (AbstractNode* node, m_nodes) { names << node->name(); }
  return names;
}

QList<AbstractNode*> Sheet::inNodes() const {
  QList<AbstractNode*> nodes;
  foreach (AbstractNode* node, m_nodes) {
    if (Input == node->io()) {
      nodes << node;
    }
  }
  return nodes;
}

int32_t Sheet::inNodeCount() const {
  return inNodes().count();
}

QList<AbstractNode*> Sheet::outNodes() const {
  QList<AbstractNode*> nodes;
  foreach (AbstractNode* node, m_nodes) {
    if (Output == node->io()) {
      nodes << node;
    }
  }
  return nodes;
}

int32_t Sheet::outNodeCount() const {
  return outNodes().count();
}

AbstractConnection* Sheet::connection(const QString& connectionName) const {
  foreach (AbstractConnection* connection, m_connections) {
    if (connectionName == connection->name()) {
      return connection;
    }
  }
  return nullptr;
}

QList<AbstractConnection*> Sheet::connections() const {
  return m_connections;
}

void Sheet::addConnection(AbstractConnection* connection) {
  m_connections << connection;
}

void Sheet::removeConnection(AbstractConnection* connection) {
  m_connections.removeOne(connection);
}

QStringList Sheet::connectionNames() const {
  QStringList names;
  foreach (AbstractConnection* connection, m_connections) { names << connection->name(); }
  return names;
}

QString Sheet::name() const {
  return m_name;
}

void Sheet::setName(const QString& name) {
  m_name = name;
}

bool Sheet::contain(const QString& figureName) const {
  foreach (AbstractNode* node, m_nodes) {
    if (figureName == node->name()) {
      return true;
    }
  }
  foreach (AbstractConnection* connection, m_connections) {
    if (figureName == connection->name()) {
      return true;
    }
  }
  return false;
}

QJsonObject Sheet::toJsonObj() {
  QJsonObject jsonObj;
  jsonObj[JSON_NAME] = m_name;
  jsonObj[JSON_ID] = m_id;

  QJsonArray nodeJsonArray;
  foreach (AbstractNode* node, m_nodes) { nodeJsonArray.append(node->toJsonObject()); }

  QJsonArray nodeToNodeConnectionJsonArray;
  QJsonArray nodeToConnectorConnectionJsonArray;
  foreach (AbstractConnection* connection, m_connections) {
    if (connection->hasStartConnector() || (connection->hasEndConnector())) {
      nodeToConnectorConnectionJsonArray << connection->toJsonObj();
    } else {
      nodeToNodeConnectionJsonArray << connection->toJsonObj();
    }
  }

  jsonObj[JSON_NODES] = nodeJsonArray;
  jsonObj[JSON_NODE_TO_NODE_CONNECTIONS] = nodeToNodeConnectionJsonArray;
  jsonObj[JSON_NODE_TO_CONNECTOR_CONNECTIONS] = nodeToConnectorConnectionJsonArray;

  return jsonObj;
}

QJsonObject Sheet::toSelectedJsonObj() {
  QJsonObject jsonObj;
  jsonObj[JSON_NAME] = m_name;
  jsonObj[JSON_ID] = m_id;

  QJsonArray nodeJsonArray;
  QList<AbstractNode*> selectedNodes;
  foreach (AbstractNode* node, m_nodes) {
    if (node->isSelected()) {
      selectedNodes << node;
      nodeJsonArray.append(node->toJsonObject());
    }
  }

  QJsonArray nodeToNodeConnectionJsonArray;
  foreach (AbstractConnection* connection, m_connections) {
    if (selectedNodes.contains(connection->startPort()->parentNode()) &&
        selectedNodes.contains(connection->endPort()->parentNode())) {
      nodeToNodeConnectionJsonArray << connection->toJsonObj();
    }
  }
  // TODO
  //  QJsonArray nodeToConnectorConnectionJsonArray;
  //  foreach (Connection* connection, m_connections) {
  //    if (connection->hasStartConnector() || (connection->hasEndConnector())) {
  //      nodeToConnectorConnectionJsonArray << connection->toJsonObj();
  //    }
  //  }

  jsonObj[JSON_NODES] = nodeJsonArray;
  jsonObj[JSON_NODE_TO_NODE_CONNECTIONS] = nodeToNodeConnectionJsonArray;
  //  jsonObj[JSON_NODE_TO_CONNECTOR_CONNECTIONS] = nodeToConnectorConnectionJsonArray;

  return jsonObj;
}
