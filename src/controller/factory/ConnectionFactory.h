#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QString>
#include <QMap>

class Connection;

class ConnectionFactory
{
public:
    static ConnectionFactory* getInstance();

    void addConnection(const QString& type, Connection* connection);
    Connection* createConnection(const QString& type, QString name = "");

private:
    QMap<QString, Connection*> m_connectionMap;

private:
    ConnectionFactory();
    ~ConnectionFactory();
};

#endif // CONNECTIONFACTORY_H
