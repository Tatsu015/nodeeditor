#include "NamePublisher.h"

const static QString SEPALATOR = "_";

NamePublisher* NamePublisher::getInstance() {
  static NamePublisher s;
  return &s;
}

void NamePublisher::addBaseName(const QString& baseName) {
  m_lastNumber[baseName] = 0;
}

QString NamePublisher::createName(const QString& baseName) {
  uint64_t lastNumber = m_lastNumber[baseName];
  uint64_t nextNum = lastNumber + 1;
  m_lastNumber[baseName] = nextNum;

  return baseName + SEPALATOR + QString::number(nextNum);
}

void NamePublisher::updateLastNumber(QString name) {
  QStringList element = name.split(SEPALATOR);
  if (element.count() < 2) {
    return;
  }

  QString baseName = element.first();
  if (!m_lastNumber.keys().contains(baseName)) {
    return;
  }

  uint64_t usedNumber = element.last().toLong();
  uint64_t lastNumber = m_lastNumber[baseName];

  if (lastNumber < usedNumber) {
    m_lastNumber[baseName] = usedNumber;
  }
}

void NamePublisher::resetNumbers() {
  foreach (QString key, m_lastNumber.keys()) { m_lastNumber[key] = 0; }
}

NamePublisher::NamePublisher() {
}

NamePublisher::~NamePublisher() {
}
