#ifndef SAVE_H
#define SAVE_H

#include "AbstractAction.h"

class QJsonObject;

class Save : public AbstractAction
{
public:
    const static QString ACTION_SAVE;

public:
    Save(QObject *parent = nullptr);
    virtual ~Save();

    virtual QAction* action();
    virtual QString name();

public slots:
    virtual void execute();

private:
    QAction* m_action = nullptr;
};

#endif // SAVE_H
