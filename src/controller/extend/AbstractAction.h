#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <QObject>

class QAction;

class AbstractAction : public QObject
{
    Q_OBJECT

public:
    explicit AbstractAction(QObject *parent = nullptr);
    virtual ~AbstractAction();

    virtual QAction* action() = 0;
    virtual QString name() = 0;

public slots:
    virtual void execute() = 0;
};

#endif // ABSTRACTACTION_H
