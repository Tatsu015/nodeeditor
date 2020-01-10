#ifndef DEFINE_H
#define DEFINE_H

#include <QString>

const static QString X = "x";
const static QString Y = "y";

enum IO : uint32_t {
  Input,
  Output,
  Hidden,
  Undefined,
};

#endif // DEFINE_H
