#ifndef OPEN_H
#define OPEN_H

#include "AbstractAction.h"

class QJsonObject;

class OpenAction : public AbstractAction
{
public:
    OpenAction(QObject *parent = nullptr);
    virtual ~OpenAction();

    virtual QString name();

public slots:
    virtual void execute();
};

#endif // OPEN_H
