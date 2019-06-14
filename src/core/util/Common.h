#ifndef COMMON_H
#define COMMON_H

#include <QString>

#define CLASS_NAME (abi::__cxa_demangle(typeid(*this).name(), 0, 0, 0))

extern QString btos(bool value);
extern bool stob(const QString& value);
extern bool between(qreal value, qreal min, qreal max);

enum EPosition : int {
  Top,
  Right,
  Bottom,
  Left,
};

enum BugType : int {
  Error,
  Warning,
};

#endif // COMMON_H
