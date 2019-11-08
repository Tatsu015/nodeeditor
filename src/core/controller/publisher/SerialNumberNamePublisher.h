#ifndef SerialNumberNamePublisher_H
#define SerialNumberNamePublisher_H

#include <QMap>
#include <QString>

class Sheet;

class SerialNumberNamePublisher {
public:
  static SerialNumberNamePublisher* getInstance();

  QString createName(const QStringList existNames, const QString& baseName, const QString& separator = "_");

private:
  SerialNumberNamePublisher();
  ~SerialNumberNamePublisher();
};

#endif // SerialNumberNamePublisher_H
