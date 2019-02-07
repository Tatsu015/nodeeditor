#ifndef NAMEPUBLISHER_H
#define NAMEPUBLISHER_H

#include <QMap>
#include <QString>

class NamePublisher {
 public:
  static NamePublisher* getInstance();

  QString createName(const QString& baseName);
  void updateLastNumber(QString name);
  void resetNumbers();

 private:
  QMap<QString, uint64_t> m_lastNumber;

 private:
  NamePublisher();
  ~NamePublisher();
};

#endif  // NAMEPUBLISHER_H
