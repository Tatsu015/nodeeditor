#ifndef OPEN_H
#define OPEN_H

#include "AbstractAction.h"

class QJsonObject;

class OpenAction : public AbstractAction
{
public:
    const static QString ACTION_OPEN;

public:
    OpenAction(QObject *parent = nullptr);
    virtual ~OpenAction();

    virtual QAction* action();
    virtual QString name();

public slots:
    virtual void execute();


private:
    QAction* m_action = nullptr;
};

#endif // OPEN_H
