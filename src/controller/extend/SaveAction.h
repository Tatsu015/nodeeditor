#ifndef SAVE_H
#define SAVE_H

#include "AbstractAction.h"

class QJsonObject;

class SaveAction : public AbstractAction
{
public:
    const static QString ACTION_SAVE;

public:
    SaveAction(QObject *parent = nullptr);
    virtual ~SaveAction();

    virtual QAction* action();
    virtual QString name();

public slots:
    virtual void execute();

private:
    QAction* m_action = nullptr;
};

#endif // SAVE_H
