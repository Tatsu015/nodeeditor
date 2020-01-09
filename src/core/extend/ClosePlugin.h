#ifndef CLOSEPLUGIN_H
#define CLOSEPLUGIN_H

#include "AbstractPlugin.h"

class ClosePlugin : public AbstractPlugin {
public:
  ClosePlugin(QObject* parent = nullptr);
  virtual ~ClosePlugin();

protected:
  void doInit();

private slots:
  void onExecute();
};

#endif // CLOSEPLUGIN_H
