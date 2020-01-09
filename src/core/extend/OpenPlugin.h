#ifndef OPENPLUGIN_H
#define OPENPLUGIN_H

#include "AbstractPlugin.h"

class OpenPlugin : public AbstractPlugin {
public:
  OpenPlugin(QObject* parent = nullptr);
  virtual ~OpenPlugin();

protected:
  void doInit();

private slots:
  void onExecute();
};

#endif // OPENPLUGIN_H
