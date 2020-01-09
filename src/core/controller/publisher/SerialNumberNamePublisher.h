#ifndef SERIALNUMBERNAMEPUBLISHER_H
#define SERIALNUMBERNAMEPUBLISHER_H

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

#endif // SERIALNUMBERNAMEPUBLISHER_H
