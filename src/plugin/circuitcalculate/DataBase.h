#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>
#include <QString>

class DataBase {
 public:
  static DataBase* getInstance();

  void write(const QString& id, bool value);
  bool read(const QString& id);
  void clear();

 private:
  QMap<QString, bool> m_db;

 private:
  DataBase();
  ~DataBase();
};

#endif  // DATABASE_H
