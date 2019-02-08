#ifndef New_H
#define New_H

#include "AbstractAction.h"

class QJsonObject;

class NewAction : public AbstractAction {
 public:
  NewAction(QObject *parent = nullptr);
  virtual ~NewAction();

  virtual QString name();

 public slots:
  virtual void execute();
};

#endif  // New_H
