#ifndef SAVE_H
#define SAVE_H

#include "AbstractAction.h"

class QJsonObject;

class SaveAction : public AbstractAction
{
public:
    SaveAction(QObject *parent = nullptr);
    virtual ~SaveAction();

    virtual QString name();

public slots:
    virtual void execute();
};

#endif // SAVE_H
