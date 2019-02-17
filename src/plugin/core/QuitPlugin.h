#ifndef QUITPLUGIN_H
#define QUITPLUGIN_H

#include "AbstractPlugin.h"

class QuitPlugin : public AbstractPlugin {
 public:
  QuitPlugin(QObject* parent = nullptr);
  virtual ~QuitPlugin();

 protected:
  void doInit();

 private slots:
  void onExecute();
};

#endif  // QUITPLUGIN_H
