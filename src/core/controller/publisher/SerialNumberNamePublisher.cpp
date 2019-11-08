#include "SerialNumberNamePublisher.h"
#include "Sheet.h"
#include <QDebug>

SerialNumberNamePublisher* SerialNumberNamePublisher::getInstance() {
  static SerialNumberNamePublisher s;
  return &s;
}

QString SerialNumberNamePublisher::createName(const QStringList existNames, const QString& baseName,
                                              const QString& separator) {
  uint64_t id = 1;
  QString name = baseName + separator + QString::number(id);
  while (existNames.contains(name)) {
    name = baseName + separator + QString::number(++id);
  }
  return name;
}

SerialNumberNamePublisher::SerialNumberNamePublisher() {
}

SerialNumberNamePublisher::~SerialNumberNamePublisher() {
}
