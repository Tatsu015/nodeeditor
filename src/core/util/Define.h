#ifndef DEFINE_H
#define DEFINE_H

#include <QString>

const static QString APP_EXTENSION = "nd";

const static QString TOOL_CONNECTION_CREATE = "ConnectionCreate";
const static QString TOOL_NODE_CREATE = "NodeCreate";
const static QString TOOL_CONNECTION_RECONNECT = "ConnectionReconnect";
const static QString TOOL_SHEET_JUMP = "SheetJump";

const static QString NODE_IN = "In";
const static QString NODE_OUT = "Out";
const static QString NODE_AND = "And";
const static QString NODE_OR = "Or";
const static QString NODE_NOT = "Not";

const static QString CONNECTION = "Connection";
const static QString CONNECTOR = "Connector";

const static QString JSON_NODE_NAME_VISIBLE = "nodeNameVisible";
const static QString JSON_ID = "id";
const static QString JSON_SHEETS = "sheets";
const static QString JSON_NODES = "nodes";
const static QString JSON_PORTS = "ports";
const static QString JSON_CONNECTORS = "connectors";
const static QString JSON_NODE_TO_NODE_CONNECTIONS = "nodeToNodeConnections";
const static QString JSON_NODE_TO_CONNECTOR_CONNECTIONS = "nodeToConnectorConnections";
const static QString JSON_NAME = "name";
const static QString JSON_NODETYPE = "nodetype";
const static QString JSON_PORT_NUMBER = "portNumber";
const static QString JSON_PORT_IO = "portIO";
const static QString JSON_PORT_INVERTED = "portInverted";
const static QString JSON_X = "x";
const static QString JSON_Y = "y";
const static QString JSON_START_NODE_NAME = "startNodeName";
const static QString JSON_START_PORT_NUMBER = "startPortNumber";
const static QString JSON_END_NODE_NAME = "endNodeName";
const static QString JSON_END_PORT_NUMBER = "endPortNumber";
const static QString JSON_CONNECTOR_POS_X_RATE = "connectorPosX";
const static QString JSON_CONNECTOR_POS_Y_RATE = "connectorPosY";
const static QString JSON_DST_CONNECTION_NAME = "dstConnectionName";

enum IO : uint32_t {
  Input,
  Output,
  Hidden,
  Undefined,
};

#endif // DEFINE_H
