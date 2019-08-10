#ifndef CutPlugin_H
#define CutPlugin_H

#include "AbstractPlugin.h"

class CutPlugin : public AbstractPlugin {
public:
  CutPlugin(QObject* parent = nullptr);
  virtual ~CutPlugin();

protected:
  void doInit();

private slots:
  void onExecute();
};

#endif // CutPlugin_H
