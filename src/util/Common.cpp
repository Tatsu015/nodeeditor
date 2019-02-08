#include "Common.h"

QString btos(bool value) {
  if (value) {
    return "true";
  }
  return "false";
}

bool stob(const QString& value) {
  if ("false" == value) {
    return false;
  }
  return true;
}

bool between(qreal value, qreal min, qreal max)
{
  if((min <= value) && (value <= max)){
    return true;
  }
  return false;
}
