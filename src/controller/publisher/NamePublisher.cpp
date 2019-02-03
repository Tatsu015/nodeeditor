#include "NamePublisher.h"

const static QString SEPALATOR = "_";

NamePublisher* NamePublisher::getInstance()
{
    static NamePublisher s;
    return &s;
}

QString NamePublisher::createName(const QString &baseName)
{
    uint64_t nowNumber = m_nextNumber[baseName];
    uint64_t nextNum   = nowNumber + 1;
    m_nextNumber[baseName] = nextNum;

    return baseName + SEPALATOR + QString::number(nowNumber);
}

void NamePublisher::updateNextNumber(QString name)
{
    QStringList element = name.split(SEPALATOR);
    if(element.count() < 2){
        return;
    }

    QString  baseName   = element.first();
    if(!m_nextNumber.keys().contains(baseName)){
        return;
    }

    uint64_t usedNumber = element.last().toLong();
    uint64_t nextNumber = m_nextNumber[baseName];

    if(nextNumber < usedNumber){
        m_nextNumber[baseName] = usedNumber;
    }
}

void NamePublisher::resetNumbers()
{
    foreach (QString key, m_nextNumber.keys()) {
        m_nextNumber[key] = 0;
    }
}

NamePublisher::NamePublisher()
{
}

NamePublisher::~NamePublisher()
{
}


