#ifndef EXITPLUGIN_H
#define EXITPLUGIN_H

#include "AbstractPlugin.h"

class ExitPlugin : public AbstractPlugin {
 public:
  ExitPlugin();
  virtual ~ExitPlugin();

 protected:
  void doInit();

 private slots:
  void onExecute();
};

#endif  // EXITPLUGIN_H
