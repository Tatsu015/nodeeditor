#ifndef OPEN_H
#define OPEN_H

#include "AbstractAction.h"

class QJsonObject;

class Open : public AbstractAction
{
public:
    const static QString ACTION_OPEN;

public:
    Open(QObject *parent = nullptr);
    virtual ~Open();

    virtual QAction* action();
    virtual QString name();

public slots:
    virtual void execute();

private:
    void fromJson(const QByteArray &data);

private:
    QAction* m_action = nullptr;
};

#endif // OPEN_H
