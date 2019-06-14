#ifndef OpenPLUGIN_H
#define OpenPLUGIN_H

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

#endif // OpenPLUGIN_H
