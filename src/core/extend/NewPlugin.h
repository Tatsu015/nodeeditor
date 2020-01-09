#ifndef NEWPLUGIN_H
#define NEWPLUGIN_H

#include "AbstractPlugin.h"

class NewPlugin : public AbstractPlugin {
public:
  NewPlugin(QObject* parent = nullptr);
  virtual ~NewPlugin();

protected:
  void doInit();

private slots:
  void onExecute();
};

#endif // NEWPLUGIN_H
