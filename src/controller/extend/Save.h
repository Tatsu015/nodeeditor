#ifndef SAVE_H
#define SAVE_H

#include "AbstractAction.h"

class Save : public AbstractAction
{
public:
    Save(QObject *parent = nullptr);
    virtual ~Save();

    virtual QAction* action();

public slots:
    virtual void execute();

private:
    QAction* m_action = nullptr;
};

#endif // SAVE_H
