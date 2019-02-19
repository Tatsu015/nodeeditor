#include "DataBase.h"

DataBase* DataBase::getInstance() {
  static DataBase s;
  return &s;
}

void DataBase::write(const QString& id, bool value) { m_db[id] = value; }

bool DataBase::read(const QString& id) { return m_db[id]; }

void DataBase::clear() { m_db.clear(); }

DataBase::DataBase() {}

DataBase::~DataBase() {}
