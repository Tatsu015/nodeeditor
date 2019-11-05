#ifndef ClosePlugin_H
#define ClosePlugin_H

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

#endif // ClosePlugin_H
