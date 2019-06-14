#ifndef DEFINE_H
#define DEFINE_H

#include <QString>

const static QString APP_EXTENSION = "nd";

const static QString TOOL_CONNECTION_CREATE = "ConnectionCreate";
const static QString TOOL_NODE_CREATE = "NodeCreate";

const static QString NODE_IN = "IN";
const static QString NODE_OUT = "OUT";
const static QString NODE_AND = "AND";
const static QString NODE_OR = "OR";

const static QString CONNECTION = "CONNECTION";

enum IO : uint32_t {
  Input,
  Output,
  Hidden,
};

#endif // DEFINE_H
