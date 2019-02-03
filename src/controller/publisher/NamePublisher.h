#ifndef NAMEPUBLISHER_H
#define NAMEPUBLISHER_H


#include <QString>
#include <QMap>

class NamePublisher
{
public:
    static NamePublisher* getInstance();

    QString createName(const QString& baseName);
    void updateNextNumber(QString name);
    void resetNumbers();

private:
    QMap<QString, uint64_t> m_nextNumber;

private:
    NamePublisher();
    ~NamePublisher();
};

#endif // NAMEPUBLISHER_H
