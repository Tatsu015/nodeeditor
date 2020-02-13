#ifndef DEFINE_H
#define DEFINE_H

#include <QString>

const static QString X = "x";
const static QString Y = "y";
const static QString CLOCK = "Clock";

enum IO : uint32_t {
  Input,
  Output,
  Hidden,
  Undefined,
};

enum Edge : uint32_t { Start, End, None };

#endif // DEFINE_H
